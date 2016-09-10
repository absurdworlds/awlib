/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <cstdio>
#include <memory>
#include <sstream>
#include <chrono>
#include <aw/utility/filesystem.h>

#include "ItdPacker.h"
#include "HPKTreeWriter.h"

namespace aw {
namespace itd {
ItdPacker::ItdPacker(std::string const& archive_name, bool verbose)
	: verbose_(verbose)
{
	archive_.open(archive_name, std::ofstream::binary);
	index_.resize(2);
}

ItdPacker::~ItdPacker()
{
	archive_.close();
}

void ItdPacker::addFile(std::string const& name)
{
	std::error_code ec;
	fs::file_status status = fs::status(name, ec);

	switch(status.type()) {
	case fs::file_type::none:
		//log.error("Error reading file" + name + ": " + ec.message());
		break;
	case fs::file_type::regular:
		try {
			index_.emplace_back(0, fs::file_size(name));
			fileList_.push_back(name);
		} catch (fs::filesystem_error) {
			//log.error("Error retrieving file size: " + name);
		}
		break;
	case fs::file_type::directory:
		addDir(name);
		break;
	default:
		//log.error(name + " is not a file or directory.");
		break;
	}
}

void ItdPacker::addList(std::vector<std::string> const& files)
{
	for (auto const & filename : files)
		addFile(filename);
}

i32 ItdPacker::pack()
{
	if (!archive_.is_open()) {
		return -1;
	}

	writeHeader();
	buildIndex();
	writeArchive();

	return 0;
}

void ItdPacker::buildIndex()
{
	std::ostringstream result;

	{
		std::unique_ptr<HPKIndexWriter> index(new HPKTreeWriter);

		for (size_t id = 0; id < fileList_.size(); ++id) {
			index->addFile(fileList_[id], id + 2);
		}

		index->write(result);
	}

	u64 num_entries = index_.size();

	index_[0].size = result.str().size();

	u64 offsetTotal = 64 + num_entries * 16;
	for (auto entry : index_) {
		entry.offset = offsetTotal;
		offsetTotal += entry.size;
		archive_.write((char *)&entry.offset,8);
		archive_.write((char *)&entry.size,8);
	}

	archive_.write(result.str().c_str(), index_[0].size);
}

i32 ItdPacker::addDir(std::string const& path)
{
	// TODO: testing and improvements
	for (auto& file : fs::directory_iterator(path))
		addFile(file.path().generic_u8string());
	return 0;
}

void ItdPacker::writeHeader()
{
	itd::MainHeader main;

	main.version = 5;
	main.numFiles = 2 + fileList_.size();

	archive_.write((char *)&main.fileId,4);
	archive_.write((char *)&main.version,2);
	archive_.write((char *)&main.flags,2);
	archive_.write((char *)&main.numFiles,8);

	using namespace std::chrono;
	auto now = steady_clock::now().time_since_epoch();

	itd::HPKHeader second;
	second.version = 5;
	second.flags = itd::HPK_HasFileTree;
	second.ptime = duration_cast<nanoseconds>(now).count();

	archive_.write((char *)&second.id,4);
	archive_.write((char *)&second.version,2);
	archive_.write((char *)&second.flags,2);
	archive_.write((char *)&second.ptime,8);
	archive_.write((char *)&second.padding, 32);
}

void ItdPacker::writeArchive() 
{
	for (size_t id = 0; id < fileList_.size(); ++id) {
		packFile(id + 2, fileList_[id]);
	}
}

void ItdPacker::packFile(size_t id, std::string const& path)
{
	std::ifstream file(path, std::ifstream::binary);

	if (!file.is_open())
		return;

	if (verbose_)
		printf("Adding %s\n", path.c_str());

	// ifstream has problems with files of zero length
	// it doesn't make sense appending zero bytes anyway
	if (index_[id].size == 0)
		return;

	archive_ << file.rdbuf();
}
} // namespace itd
} // namespace aw
