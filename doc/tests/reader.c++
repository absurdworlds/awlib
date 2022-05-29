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
#include <aw/doc/utility.h>
#include <aw/doc/parser.h>

using namespace aw;
using namespace aw::io;
using namespace aw::doc;

void print_node(const doc::node& parent, std::string name = "")
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

int main(int,char** arg)
{
	if (arg[1] == nullptr)
		return 1;

	ostream_logger log{std::cout};
	// open a file
	io::input_file_stream stream{arg[1]};
	// create the parser

	auto begin = std::chrono::steady_clock::now();
	auto doc = doc::parse_file( stream, &log );
	auto end = std::chrono::steady_clock::now();
	print_node( doc.root() );

	std::cerr << "parse time: " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << "ns (";
	std::cerr << std::chrono::duration_cast<std::chrono::duration<double>>(end - begin).count() << "s)\n";
}
