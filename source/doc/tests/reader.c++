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
#include <aw/doc/parser.h>

using namespace aw;
using namespace aw::io;
using namespace aw::doc;

/*!
 * \example doc_example.cpp
 *
 * This file provides an usage example for doc::parser,
 * messages.doc is used as an example document here.
 */

typedef std::map<std::string, value> Document;

void parseObject(doc::parser* parser, std::string parent, Document& doc);
void parseNode(doc::parser* parser, std::string name, std::string node, Document& doc);
void parsevalue(doc::parser* parser, std::string name, std::string node, Document& doc);

void parseDocument(doc::parser* parser, Document& doc)
{
	doc::object obj;
	while (parser->read(obj)) {
		if (obj.kind != doc::object::node)
			continue;

		doc[obj.name] = value();
		parseObject(parser, obj.name, doc);
	}
}

void parseObject(doc::parser* parser, std::string parent, Document& doc)
{
	doc::object obj;
	while (parser->read(obj)) {
		std::string& name = obj.name;

		switch (obj.kind) {
		case doc::object::node:
			parseObject(parser, parent + "." + name, doc);
			doc[parent + "." + name] = value();
			break;
		case doc::object::value:
			doc[parent + "." + name] = obj.val;
			break;
		case doc::object::end:
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
	parser parser{stream, &log};

	Document doc;

	auto begin = std::chrono::steady_clock::now();
	parseDocument(&parser, doc);
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
