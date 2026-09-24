/*
 * Copyright (C) 2015  hedede <Haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <chrono>

#include <aw/log/ostream_logger.h>
#include <aw/io/input_file_stream.h>
#include <aw/hudf/utility.h>
#include <aw/hudf/parser.h>

using namespace aw;
using namespace aw::io;
using namespace aw::hudf;

void print_node(const node& parent, std::string name = "")
{
	for (const auto& n : parent.children) {
		auto child_name = name + "/" + n.name;
		std::cout << child_name;
		if (n.value)
			std::cout << " = " << to_string(n.value);
		std::cout << '\n';
		print_node( n, child_name );
	}
}

int main(int, char** arg)
{
	if (arg[1] == nullptr)
		return 1;

	bool has_error = false;

	int i = 1;
	for (int i = 1; arg[i] != nullptr; ++i)
	{
		ostream_logger log{std::cout};
		// open a file
		io::input_file_stream stream{arg[i]};
		// create the parser

		auto begin = std::chrono::steady_clock::now();
		hudf::parser parser(stream, &log);
		aw::document doc( hudf::parse_node(parser) );
		auto end = std::chrono::steady_clock::now();

		has_error += parser.has_error();

		print_node( doc.root() );


		std::cerr << "parse time: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << "ns (";
		std::cerr << std::chrono::duration_cast<std::chrono::duration<double>>(end - begin).count() << "s)\n";
	}

	return has_error ? EXIT_FAILURE : EXIT_SUCCESS;
}
