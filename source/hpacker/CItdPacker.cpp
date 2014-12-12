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

#include <hrengin/io/filesystem.h>
#include <hrengin/io/IDirectory.h>

#include "CItdPacker.h"

namespace hrengin {
namespace itd {
CItdPacker::CItdPacker (std::string const& archive_name, bool verbose)
	: verbose_(verbose)
{
	archive_.open(archive_name, std::ofstream::binary);
}

CItdPacker::~CItdPacker ()
{
	archive_.close();
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
	if(!archive_.is_open()) {
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

	index_[0].offset = archive_.tellp();

	root.write(archive_);

	index_[0].size  = archive_.tellp();
	index_[0].size -= index_[0].offset;
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

	header.main.version = 3;
	header.main.ptime = getTime();
	header.main.files_num = 2 + fileList_.size();
	
	archive_.write((char *)&header.main.fileId,4);
	archive_.write((char *)&header.main.version,4);
	archive_.write((char *)&header.main.ptime,8);
	archive_.write((char *)&header.main.files_num,8);
	archive_.write((char *)&header.main.flags,2);
	archive_.write((char *)&header.main.padding, 6);

	itd::StandardHeader second;
	second.version = 2;
	second.flags = itd::STD_HasFileTree;

	archive_.write((char *)&second.id,4);
	archive_.write((char *)&second.version,4);
	archive_.write((char *)&second.flags,4);
	archive_.write((char *)&second.padding, 20);
}

void CItdPacker::prepareFileIndex ()
{
	// Number of files + file tree and hashtable
	u64 num_entries = 2 + fileList_.size();
	index_.resize(num_entries);

	// Reserve space for file index
	writeFileIndex();

}

void CItdPacker::writeArchive() 
{
	for(size_t id = 0; id < fileList_.size(); ++id) {
		packFile(id + 2, fileList_[id]);
	}
}

void CItdPacker::packFile (size_t id, std::string const& path)
{
	std::ifstream file(path, std::ifstream::binary);

	if(!file.is_open()) {
		index_[id].offset = -1;
		index_[id].size   =  0;
		return;
	}

	if(verbose_) {
		printf("Adding %s\n", path.c_str());
	}

	index_[id].offset = archive_.tellp();

	archive_ << file.rdbuf();

	index_[id].size  = archive_.tellp();
	index_[id].size -= index_[id].offset;
}

void CItdPacker::updateFileIndex ()
{
	archive_.seekp(64);

	writeFileIndex();
}

void CItdPacker::writeFileIndex ()
{
	for(auto entry : index_) {
		archive_.write((char *)&entry.offset,8);
		archive_.write((char *)&entry.size,8);
	}
}

} // namespace itd
} // namespace hrengin
