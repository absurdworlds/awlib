/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <cstdio>
#include <iostream>

#include <aw/utility/argv_parser.h>
#include <aw/utility/string/split.h>
#include <aw/io/filesystem.h>

#include "hpacker.h"

namespace aw {
namespace itd {
void printUsage()
{
	printf("Usage: hpacker [OPTION]... [FILE...]\n");
	printf("hpacker is a utility which packs files together into ITD archive.\n");
	printf("\n");
	printf("  -c, --create         Create an archive\n");
	printf("  -x, --extract-all    Extract contents of archive\n");
	printf("  -e, --extract        Extract files from FILE list\n");
	printf("  -i, --indices        With extract option, use file indices instead of names\n");
	printf("  -l, --list           List contents of archive\n");
	printf("  -f, --file NAME      Perform actions on file NAME\n");
	printf("  -v, --verbose        Show verbose output\n");
	printf("  -h, --help           Display this message\n");

}

i32 main (char** args)
{
	if (!*(args+1))
		printUsage();

	utils::argv_parser argp(args+1);

	enum Action {
		None,
		Create,
		Unpack,
		Extract,
		ExtractAll,
		List
	} action;

	std::string filename;
	std::vector<std::string> files;
	bool verbose = false;
	bool indices = false;

	optional<utils::argument> opt_arg;
	while (opt_arg = argp.parse_argument()) {
		utils::argument& arg = opt_arg.value();
		if (arg.type == utils::argument::option) {
			if(arg.name == "c" || arg.name == "create") {
				action = Create;
			} else if (arg.name == "l" || arg.name == "list") {
				action = List;
			} else if (arg.name == "x" || arg.name == "extract-all") {
				action = ExtractAll;
			} else if (arg.name == "e" || arg.name == "extract") {
				action = Extract;
			} else if (arg.name == "f" || arg.name == "file") {
				filename = argp.get_param();
			} else if (arg.name == "v" || arg.name == "verbose") {
				verbose = true;
			} else if (arg.name == "i" || arg.name == "indices") {
				indices = true;
			}
#if 0
		if(arg.type == core::Argument::Option && arg.name == "-") {
			// from stdin
		}
#endif

			if (arg.name == "h" || arg.name == "help") {
				printUsage();
			}
		} else if (arg.type == utils::argument::operand) {
			if (!action) {
				fprintf(stderr, "No action selected\n");
				fprintf(stderr, "Type hpacker -h or hpacker --help for usage.\n");
				return -1;
			} else {
				files.push_back(arg.name);
			}
		}
	}

	std::fstream file;

	auto istream = [&file, filename]() -> std::istream& {
		if (!filename.empty())
			file.open(filename, std::ios::in|std::ios::binary);
		return filename.empty() ? std::cin : file;
	};


	auto ostream = [&file, filename]() -> std::ostream& {
		if (!filename.empty())
			file.open(filename, std::ios::out|std::ios::binary|std::ios::trunc);
		return filename.empty() ? std::cout : file;
	};


	if (action == Create) {
		ItdPacker packer(ostream(), verbose);
		packer.addList(files);

		packer.pack();
	} else if (action == List) {
		ItdReader reader(istream(), verbose);
		auto list = reader.list("");

		for (auto file : list) {
			printf("%s\n",file.c_str());
		}
	} else if (action == Extract) {
		ItdReader reader(istream(), verbose);

		if (indices)
		{
			//TODO: obtain the file name
			//auto list = reader.list("");
			for (const auto& file : files)
			{
				u64 index;
				try {
					index = std::stoull(file);
				} catch(...) {
					continue;
				}
				if (verbose)
					std::cout << "Extracting: " << index << '\n';
				std::ofstream f(file, std::ios::binary);
				auto v = reader.getFileContents(index);
				f.write((char*)v.data(),v.size());
			}
			return 0;
		}

		for (auto file : files) {
			std::string path(string::split(file,"/").back());
			std::ofstream f(path, std::ios::binary);
			auto v = reader.getFileContents(file);
			f.write((char*)v.data(),v.size());
		}
	} else if (action == ExtractAll) {
		ItdReader reader(istream(), verbose);
		auto list = reader.list("");

		for (auto file : list) {
			fs::path path(file);
			std::error_code ec;
			fs::create_directories(path.relative_path().parent_path(), ec);
			if (verbose)
				printf("%s\n",file.c_str());
			std::ofstream f(path.relative_path().u8string(), std::ios::binary);
			auto v = reader.getFileContents(file);
			f.write((char*)v.data(),v.size());
		}
	}


	return 0;
}

} // namespace itd
} // namespace aw

int main(int, char** argv)
{
	return aw::itd::main(argv);
}
