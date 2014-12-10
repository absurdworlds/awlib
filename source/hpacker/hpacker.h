/* This file is a part of hrengin library collection
 *
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 2.1 <http://gnu.org/licenses/lgpl-2.1.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_CArgParser_
#define _hrengin_CArgParser_
#include <string>
#include <vector>
#include <cstring>
#include <algorithm>

#include <hrengin/common/types.h>
#include <hrengin/common/stringutils.h>
#include <hrengin/hitd/hitd.h>
#include <hrengin/io/CWriteFile.h>

namespace hrengin {
namespace itd {

struct FileTree {
	typedef std::pair<std::string, size_t> file_entry;
	typedef std::pair<std::string, FileTree> leaf_type;


	std::vector<leaf_type> leaves_;
	std::vector<file_entry> files_;

	void addFile (std::string const& path, u64 id)
	{
		std::vector<std::string> tokens;
		size_t depth = splitString(path, "/", tokens);

		addFile(tokens, id);
	}

	void addFile (std::vector<std::string> path, u64 id)
	{
		size_t depth = path.size();

		if(depth > 1) {
			findAndAdd(path.front(),
				std::vector<std::string>(
						path.begin()+1,
						path.end()
					), id);
		} else if(depth == 1) {
			files_.push_back(file_entry(path.back(), id));
		}
	}

	void findAndAdd (std::string const& name,
		std::vector<std::string> path, u64 id)
	{
		auto findChild = [&name] (leaf_type const& pair)
		{
			return (pair.first == name);
		};

		auto found = std::find_if(std::begin(leaves_), 
				std::end(leaves_), findChild);

		FileTree* child;

		if(found != std::end(leaves_)) {
			child = &found->second;
		} else {
			FileTree newChild;
			leaves_.push_back(leaf_type(name, newChild)); 
			child = &leaves_.back().second;
		}

		child->addFile(path, id);
	}
};

class CItdPacker {
public:	
	CItdPacker (std::string const& archive_name, bool verbose = false);
	~CItdPacker ();

	/*!
	 * Add file to archive
	 */
	void addFile (std::string const& filename);
	/*!
	 * Add list of files
	 */
	void addList (std::vector<std::string> const& files);
	/*!
	 * Pack archive
	 */
	i32 pack ();

private:
	void buildFileList ();
	void addObject (std::string const& path);
	i32 addDir (std::string const& path);

	void writeHeader();

	void prepareFileIndex ();
	void updateFileIndex ();

	void buildFileTree ();

	void writeArchive();
	void packFile (size_t id, std::string const& path);

	std::vector<std::string> inputFiles_;
	std::vector<std::string> fileList_;
	std::vector<itd::FileEntry> index_;

	io::CWriteFile archive_;

	bool verbose_;
};
} // namespace itd
} // namespace hrengin
#endif//_hrengin_CArgParser_
