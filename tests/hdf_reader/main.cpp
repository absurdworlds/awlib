#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <iostream>

#include <awengine/io/ReadFile.h>
#include <awengine/io/InputFileStream.h>
#include <awengine/hdf/Parser.h>

using namespace awrts;
using namespace io;
using namespace hdf;

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
	io::ReadFile file(arg[1]);
	InputFileStream stream(file);
	// create the parser
	Parser* hdf = hdf::createParser(stream);

	Document doc;

	parseDocument(hdf, doc);

	for (auto pair : doc) {
		std::cout << pair.first;
		std::string const val = as_string(pair.second);
		if (val == "") {
			std::cout << "\n";
			continue;
		}

		std::cout << " = " << as_string(pair.second) << "\n";
	}

	delete hdf;
}
