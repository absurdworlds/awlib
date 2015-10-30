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

// function to for parsing a single node
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


std::string to_string(Value val)
{
	switch (val.getType()) {
	case hdf::Type::String:
		{
			std::string v;
			val.get(v);
			return v;
		}
	case hdf::Type::Float:
		{
			f64 f;
			val.get(f);
			return std::to_string(f);
		}
	case hdf::Type::Integer:
		{
			i64 i;
			val.get(i);
			return std::to_string(i);
		}
	case hdf::Type::Boolean:
		{
			bool b;
			val.get(b);
			return std::to_string(b);
		}
	case hdf::Type::Vector2d:
		{
			Vector2d<f32> v;
			val.get(v);
			return std::to_string(v[0]) + ", " + std::to_string(v[1]);
		}
	case hdf::Type::Vector3d:
		{
			Vector3d<f32> v;
			val.get(v);
			return std::to_string(v[0]) + ", " + std::to_string(v[1]) + ", " + std::to_string(v[2]);
		}
	case hdf::Type::Vector4d:
		{
			Vector4d<f32> v;
			val.get(v);
			return std::to_string(v[0]) + ", " + std::to_string(v[1]) + ", " + std::to_string(v[2]) + ", " + std::to_string(v[3]);
		}
	}

	return "";
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
		std::string const val = to_string(pair.second);
		if (val == "") {
			std::cout << "\n";
			continue;
		}

	       	std::cout << " = " << to_string(pair.second) << "\n";
	}

	delete hdf;
}
