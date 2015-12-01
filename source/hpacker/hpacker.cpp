/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 2.1 <http://gnu.org/licenses/lgpl-2.1.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <cstdio>

#include <aw/core/ArgParser.h>

#include "hpacker.h"

namespace aw {
namespace itd {
void printUsage()
{
	printf("Usage: hpacker [OPTION]... [FILE...]\n");
	printf("hpacker is a utility which serves files together into a TD archive.\n");
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
	core::ArgParser* argp = core::createArgParser(args+1);

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
		ItdPacker packer(filename, verbose);
		packer.addList(files);

		packer.pack();
	}

	return 0;
}

} // namespace itd
} // namespace aw

int main (int, char** argv)
{
	return aw::itd::main(argv);
}
