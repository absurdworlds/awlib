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
#include <memory>
#include <sstream>

#include <hrengin/platform/time.h>

#include <hrengin/io/filesystem.h>
#include <hrengin/io/IDirectory.h>

#include "CItdPacker.h"
#include "CHPKTreeWriter.h"

namespace hrengin {
namespace itd {
CItdPacker::CItdPacker (std::string const& archive_name, bool verbose)
	: verbose_(verbose)
{
	archive_.open(archive_name, std::ofstream::binary);
	index_.resize(2);
}

CItdPacker::~CItdPacker ()
{
	archive_.close();
}

void CItdPacker::addFile (std::string const& name)
{
	if(checkFile(name, io::FM_Read) < 0) {
		// log warning
		return;
	}

	io::FileInfo finfo;
	io::fileStat(name, finfo);

	switch(finfo.type) {
	case io::FileType::File:
		fileList_.push_back(name);
		FileEntry e;
		e.size = finfo.size;
		index_.push_back(e);
		break;

	case io::FileType::Dir:
		addDir(name);
		break;

	default:
		break;
	}
}

void CItdPacker::addList (std::vector<std::string> const& files)
{
	for(auto const & filename : files) {
		addFile(filename);
	}
}

i32 CItdPacker::pack ()
{
	if(!archive_.is_open()) {
		return -1;
	}
	
	writeHeader();
	buildIndex();
	writeArchive();

	return 0;
}

void CItdPacker::buildIndex ()
{
	std::ostringstream result;

	{
		std::unique_ptr<IHPKIndexWriter> index(new CHPKTreeWriter);

		for(size_t id = 0; id < fileList_.size(); ++id) {
			index->addFile(fileList_[id], id + 2);
		}

		index->write(result);
	}

	u64 num_entries = index_.size();

	index_[0].size = result.str().size();

	u64 offsetTotal = 64 + num_entries * 16;
	for(auto entry : index_) {
		entry.offset = offsetTotal;
		offsetTotal += entry.size;
		archive_.write((char *)&entry.offset,8);
		archive_.write((char *)&entry.size,8);
	}
	
	archive_.write(result.str().c_str(),index_[0].size);
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

		addFile (path + "/" + file.name);
	};

	return 0;
}

void CItdPacker::writeHeader()
{
	itd::MainHeader main;

	main.version = 5;
	main.numFiles = 2 + fileList_.size();
	
	archive_.write((char *)&main.fileId,4);
	archive_.write((char *)&main.version,2);
	archive_.write((char *)&main.flags,2);
	archive_.write((char *)&main.numFiles,8);

	itd::HPKHeader second;
	second.version = 5;
	second.flags = itd::HPK_HasFileTree;
	second.ptime = getTime();

	archive_.write((char *)&second.id,4);
	archive_.write((char *)&second.version,2);
	archive_.write((char *)&second.flags,2);
	archive_.write((char *)&second.ptime,8);
	archive_.write((char *)&second.padding, 32);
}

void CItdPacker::writeArchive () 
{
	for(size_t id = 0; id < fileList_.size(); ++id) {
		packFile(id + 2, fileList_[id]);
	}
}

void CItdPacker::packFile (size_t id, std::string const& path)
{
	std::ifstream file(path, std::ifstream::binary);

	if(!file.is_open()) {
		return;
	}

	if(index_[id].size == 0) {
		return;
	}

	if(verbose_) {
		printf("Adding %s\n", path.c_str());
	}

	archive_ << file.rdbuf();
}
} // namespace itd
} // namespace hrengin
