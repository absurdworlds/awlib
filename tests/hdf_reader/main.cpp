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

#include <aw/io/input_file_stream.h>
#include <aw/hdf/Parser.h>

using namespace aw;
using namespace aw::io;
using namespace aw::hdf;

/*!
 * \example hdf_example.cpp
 *
 * This file provides an usage example for hdf::Parser,
 * messages.hdf is used as an example document here.
 */

typedef std::map<std::string, Value> Document;

void parseObject(Parser* hdf, std::string parent, Document& doc);
void parseNode(Parser* hdf, std::string name, std::string node, Document& doc);
void parseValue(Parser* hdf, std::string name, std::string node, Document& doc);

void parseDocument(Parser* hdf, Document& doc)
{
	while (hdf->read()) {
		hdf::Object obj = hdf->getObject();
		std::string& name = obj.name;

		if (obj.type != hdf::Object::Node)
			continue;

		doc[name] = Value();
		parseObject(hdf, name, doc);
	}
}

void parseObject(Parser* hdf, std::string parent, Document& doc)
{
	while (hdf->read()) {
		hdf::Object obj = hdf->getObject();
		std::string& name = obj.name;

		switch (obj.type) {
		case hdf::Object::Node:
			parseNode(hdf, name, parent, doc);
			break;
		case hdf::Object::Value:
			parseValue(hdf, name, parent, doc);
			break;
		case hdf::Object::NodeEnd:
			return;
		default:
			break;
		}
	}
}

void parseNode(Parser* hdf, std::string name, std::string node, Document& doc)
{
	parseObject(hdf, node + "." + name, doc);

	doc[node + "." + name] = Value();
}

void parseValue(Parser* hdf, std::string name, std::string node, Document& doc)
{
	Value v;
	hdf->readValue(v);

	doc[node + "." + name] = v;
}

int main(int,char** arg)
{
	if (arg[1] == 0)
		return 1;

	// open a file
	io::input_file_stream stream(arg[1]);
	// create the parser
	Parser* hdf = hdf::createParser(stream);

	Document doc;

	auto begin = std::chrono::steady_clock::now();
	parseDocument(hdf, doc);
	auto end = std::chrono::steady_clock::now();

	std::cerr << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << '\n';
	std::cerr << std::chrono::duration_cast<std::chrono::duration<double>>(end - begin).count() << '\n';

	for (auto pair : doc) {
		std::cout << pair.first;
		std::string const val = to_string(pair.second);
		if (val == "") {
			std::cout << "\n";
			continue;
		}

		std::cout << " = " << to_string(pair.second) << "\n";
	}

	delete hdf;
}
