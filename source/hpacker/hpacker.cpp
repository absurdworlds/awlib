/* This file is a part of hrengin library collection
 *
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 2.1 <http://gnu.org/licenses/lgpl-2.1.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <cstdio>

#include <hrengin/platform/time.h>
#include <hrengin/io/CReadFile.h>
#include <hrengin/io/filesystem.h>
#include <hrengin/io/IDirectory.h>
#include <hrengin/core/IArgParser.h>

#include "hpacker.h"

namespace hrengin {
namespace itd {
CItdPacker::CItdPacker (std::string const& archive_name)
	: name_(archive_name), archive_(name_, io::FileMode::Overwrite)
{	
}

CItdPacker::~CItdPacker ()
{
	remove((name_ + ".tmp.1").c_str());
}

void CItdPacker::add_file (std::string const& filename)
{
	//TODO? check for validity
	files_to_pack_.push_back(filename);
}

i32 CItdPacker::pack ()
{
	if(!archive_.isOpen()) {
		return -1;
	}
	pack_archive();

	write_header();
	write_index();
	write_archive();

	return 0;
}

i32 CItdPacker::pack_archive ()
{
	io::CWriteFile tmp(name_ + ".tmp.1", io::FileMode::Overwrite);

	if(!tmp.isOpen()) {
		return -1;
	}

	for(auto file : files_to_pack_) {
		pack_object(file, tmp);
	}

	return 0;
}

i32 CItdPacker::pack_object (std::string const& file, io::CWriteFile& tmp)
{
	io::FileInfo finfo = io::file_stat(file);

	switch(finfo.type) {
	case io::FileType::File:
		pack_file(file, tmp);
		break;
	case io::FileType::Dir:
		pack_dir(file, tmp);
		break;
	default:
		return -1;
	}

	return 0;
}


i32 CItdPacker::pack_dir (std::string const& path, io::CWriteFile& tmp)
{
	io::IDirectory* dir = io::openDirectory(path);
	if(!dir) {
		return -1;
	}

	io::Dirent file;
	while(dir->read(file)) {
		if(file.name == "." || file.name == "..") {
			continue;
		}

		pack_object (path + "/" + file.name, tmp);
	};

	return 0;

}

i32 CItdPacker::pack_file (std::string const& path, io::CWriteFile& tmp)
{
	io::CReadFile in(path);

	if(!in.isOpen()) {
		return -1;
	}
	
	//printf("Adding: %s\n",(path + "/" + file.name).c_str());

	itd::FileEntry entry;
	entry.offset = tmp.tell();
	entry.size   = in.getSize();
	entry.mtime  = 0;
	entry.flags  = itd::FileFlags::None;
	index_.push_back(entry);

	char* buf = new char[entry.size];

	in.read(buf, entry.size);
	tmp.write(buf, entry.size);

	delete[] buf;

	return 0;
}

void CItdPacker::write_header()
{
	itd::Header header;
	header.fileId = 'h' + ('i' << 8) + ('t' << 16) + ('d' << 24);
	header.version = 1;
	header.ptime = getTime();
	header.secondId = 'h' + ('p' << 8) + ('k' << 16) + ('a' << 24);

	archive_.write(&header.fileId,4);
	archive_.write(&header.version,4);
	archive_.write(&header.ptime,8);
	archive_.write(&header.secondId,4);
	archive_.write(&header.padding, 44);

	// File index starts at offset 64
	globalOffset_ = 64;

}

void CItdPacker::write_index()
{
	globalOffset_ += index_.size()*32;

	for(auto e : index_) {
		e.offset += globalOffset_;
		archive_.write(&e.offset,8);
		archive_.write(&e.size,8);
		archive_.write(&e.mtime,8);
		archive_.write(&e.flags,2);
		archive_.write(&e.padding[0],6);
	}
}

i32 CItdPacker::write_archive() 
{
	io::CReadFile in(name_ + ".tmp.1");

	char buf[4096];
	i32 num;
	while((num = in.read(&buf, 4096))) {
		//printf("%d;%d\n",in->tell(),in->getSize());
		if(num > 0) {
			archive_.write(buf, num);
		}
	}

	return 0;
}

i32 main (char** args)
{
	core::IArgParser* argp = core::createArgParser(args);

	enum Action {
		None,
		Create,
		Unpack,
		List
	} action;

	std::string filename;
	std::vector<std::string> files;
	std::string dir;

	core::ClineArg arg;
	while(argp->getToken(arg)) {
		if(arg.type == core::ClineArg::Option) {
			if(arg.name == "c" || arg.name == "create") {
				action = Create;
			}

			if(arg.name == "l" || arg.name == "list") {
				action = List;
			}

			if(arg.name == "e" || arg.name == "extract") {
				action = List;
			}

			if(arg.name == "f" || arg.name == "file") {
				argp->getToken(arg);
				filename = arg.name;
			}
#if 0
		if(arg.type == core::ClineArg::Option && arg.name == "-") {
			// from stdin
		}
#endif

			if(arg.name == "h" || arg.name == "help") {
				printf("Usage: hpacker [OPTION]... [FILE...]\n");
				printf("\n");
				printf("  -c, --create         Create an archive\n");
				printf("  -e, --extract        Extract contents of archive\n");
				printf("  -l, --list           List contents of archive\n");
				printf("  -f, --file NAME      Perform actions on file NAME\n");
				printf("  -h, --help           Display this message\n");
			}

		} else if(arg.type == core::ClineArg::Argument) {
			if(!action) {
				fprintf(stderr, "No action selected\n");
				fprintf(stderr, "Type hpacker -h or hpacker --help for usage.\n");			
				return -1;
			} else {
				files.push_back(arg.name);
			}
		}
	}
	
	argp->getToken(arg);
	dir = arg.name;
	
	if(action == Create) {
		CItdPacker packer(filename);
		for(auto f : files) {
			packer.add_file(f);
		}

		packer.pack();
	}

	return 0;
}

} // namespace itd
} // namespace hrengin

int main (int, char** argv)
{
	return hrengin::itd::main(argv);
}
