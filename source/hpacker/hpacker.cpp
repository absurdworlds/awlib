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
#include <cstring>

#include <hrengin/platform/time.h>
#include <hrengin/io/CReadFile.h>
#include <hrengin/io/filesystem.h>
#include <hrengin/io/IDirectory.h>
#include <hrengin/core/IArgParser.h>

#include "hpacker.h"

namespace hrengin {
namespace itd {
CItdPacker::CItdPacker (std::string const& archive_name, bool verbose)
	: archive_(archive_name, io::FileMode::Overwrite), verbose_(verbose)
{	
}

CItdPacker::~CItdPacker ()
{
}

void CItdPacker::addFile (std::string const& filename)
{
	inputFiles_.push_back(filename);
}

void CItdPacker::addList (std::vector<std::string> const& files)
{
	inputFiles_.insert(inputFiles_.end(), files.begin(), files.end());
}

i32 CItdPacker::pack ()
{
	if(!archive_.isOpen()) {
		return -1;
	}
	
	buildFileList();
	writeHeader();
	prepareFileIndex();
	buildFileTree();
	writeArchive();
	updateFileIndex();

	return 0;
}

void CItdPacker::buildFileList ()
{
	while(!inputFiles_.empty()) {
		addObject(inputFiles_.back());
		inputFiles_.pop_back();
	}
}

void CItdPacker::buildFileTree ()
{
	FileTree root;
	for(size_t id = 0; id < fileList_.size(); ++id) {
		root.addFile(fileList_[id], id + 2);
	}

	index_[0].offset = archive_.tell();

	root.write(archive_);

	index_[0].size = archive_.tell() - index_[0].offset;
}

void CItdPacker::addObject (std::string const& path)
{
	io::FileInfo finfo;
	io::fileStat(path, finfo);

	switch(finfo.type) {
	case io::FileType::File:
		fileList_.push_back(path);
		break;

	case io::FileType::Dir:
		addDir(path);
		break;

	default:
		break;
	}
}

i32 CItdPacker::addDir (std::string const& path)
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

		addObject (path + "/" + file.name);
	};

	return 0;
}

void CItdPacker::writeHeader()
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
}

void CItdPacker::prepareFileIndex ()
{
	// Number of files + file tree and hashtable
	u64 num_entries = 2 + fileList_.size();
	index_.resize(num_entries);

	// Write empty index
	for(auto entry : index_) {
		archive_.write(&entry.offset,8);
		archive_.write(&entry.size,8);
		archive_.write(&entry.mtime,8);
		archive_.write(&entry.flags,2);
		archive_.write(&entry.padding[0],6);
	}
}

void CItdPacker::writeArchive() 
{
	for(size_t id = 0; id < fileList_.size(); ++id) {
		packFile(id + 2, fileList_[id]);
	}
}

void CItdPacker::packFile (size_t id, std::string const& path)
{
	io::CReadFile file(path);

	if(!file.isOpen()) {
		index_[id].offset = -1;
		index_[id].size   =  0;
		return;
	}

	if(verbose_) {
		printf("Adding %s\n", path.c_str());
	}

	size_t size = file.getSize();

	index_[id].offset = archive_.tell();
	index_[id].size = size;
	index_[id].mtime = 0;
	index_[id].flags = itd::FileFlags::None;

	char* buf = new char[size];

	file.read(buf, size);
	archive_.write(buf, size);

	delete[] buf;
}

void CItdPacker::updateFileIndex ()
{
	archive_.seek(64);
	for(auto entry : index_) {
		archive_.write(&entry.offset,8);
		archive_.write(&entry.size,8);
		archive_.write(&entry.mtime,8);
		archive_.write(&entry.flags,2);
		archive_.write(&entry.padding[0],6);
	}
}

void printUsage()
{
	printf("Usage: hpacker [OPTION]... [FILE...]\n");
	printf("hpacker is a utility which serves files together into a ITD archive.\n");
	printf("\n");
	printf("  -c, --create         Create an archive\n");
	printf("  -e, --extract        Extract contents of archive\n");
	printf("  -l, --list           List contents of archive\n");
	printf("  -f, --file NAME      Perform actions on file NAME\n");
	printf("  -v, --verbose        Show verbose output\n");
	printf("  -h, --help           Display this message\n");

}

i32 main (char** args)
{
	core::IArgParser* argp = core::createArgParser(args+1);

	enum Action {
		None,
		Create,
		Unpack,
		List
	} action;

	std::string filename;
	std::vector<std::string> files;
	bool verbose = false;

	core::ClineArg arg;
	while(argp->getToken(arg)) {
		if(arg.type == core::ClineArg::Option) {
			if(arg.name == "c" || arg.name == "create") {
				action = Create;
			} else if(arg.name == "l" || arg.name == "list") {
				action = List;
			} else if(arg.name == "e" || arg.name == "extract") {
				action = List;
			} else if(arg.name == "f" || arg.name == "file") {
				argp->getToken(arg);
				filename = arg.name;
			} else if(arg.name == "v" || arg.name == "verbose") {
				verbose = true;
			}
#if 0
		if(arg.type == core::ClineArg::Option && arg.name == "-") {
			// from stdin
		}
#endif

			if(arg.name == "h" || arg.name == "help") {
				printUsage();
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
	
	if(action == Create) {
		CItdPacker packer(filename, verbose);
		packer.addList(files);

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
