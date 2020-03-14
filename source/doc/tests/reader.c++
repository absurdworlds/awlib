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
#include <aw/fileformat/hdf/parser.h>

using namespace aw;
using namespace aw::io;
using namespace aw::hdf;

/*!
 * \example hdf_example.cpp
 *
 * This file provides an usage example for hdf::parser,
 * messages.hdf is used as an example document here.
 */

typedef std::map<std::string, value> Document;

void parseObject(parser* hdf, std::string parent, Document& doc);
void parseNode(parser* hdf, std::string name, std::string node, Document& doc);
void parsevalue(parser* hdf, std::string name, std::string node, Document& doc);

void parseDocument(parser* hdf, Document& doc)
{
	hdf::object obj;
	while (hdf->read(obj)) {
		if (obj.kind != hdf::object::node)
			continue;

		doc[obj.name] = value();
		parseObject(hdf, obj.name, doc);
	}
}

void parseObject(parser* hdf, std::string parent, Document& doc)
{
	hdf::object obj;
	while (hdf->read(obj)) {
		std::string& name = obj.name;

		switch (obj.kind) {
		case hdf::object::node:
			parseObject(hdf, parent + "." + name, doc);
			doc[parent + "." + name] = value();
			break;
		case hdf::object::value:
			doc[parent + "." + name] = obj.val;
			break;
		case hdf::object::end:
			return;
		default:
			break;
		}
	}
}


int main(int,char** arg)
{
	if (arg[1] == 0)
		return 1;

	ostream_logger log{std::cout};
	// open a file
	io::input_file_stream stream{arg[1]};
	// create the parser
	parser hdf{stream, &log};

	Document doc;

	auto begin = std::chrono::steady_clock::now();
	parseDocument(&hdf, doc);
	auto end = std::chrono::steady_clock::now();

	std::cerr << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << '\n';
	std::cerr << std::chrono::duration_cast<std::chrono::duration<double>>(end - begin).count() << '\n';

	for (auto& pair : doc) {
		std::cout << pair.first;
		std::string const val = to_string(pair.second);
		if (val == "") {
			std::cout << "\n";
			continue;
		}

		std::cout << " = " << to_string(pair.second) << "\n";
	}
}
