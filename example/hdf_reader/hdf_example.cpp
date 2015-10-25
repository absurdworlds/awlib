#include <fstream>
#include <string>
#include <vector>

#include <awengine/io/ReadFile.h>
#include <awengine/io/InputFileStream.h>
#include <awengine/hdf/Parser.h>

using namespace awrts;
using namespace io;
using namespace hdf;

/*!
 * \example hdf_example.cpp
 *
 * This file provides an usage example for IHDFParser,
 * messages.hdf is used as an example document here.
 */

// the struct representing a message
struct Message {
	struct color {
		u8 red;
		u8 green;
		u8 blue;
	} color;
	std::string text;
};

// function to for parsing a single node
void parseNode(Parser* hdf, std::string node, Message& msg)
{
	// any object must be read strictly in this order
	while(hdf->read()) {
		hdf::Object type = hdf->getObjectType();
		std::string name;

		switch(type) {
		case hdf::Object::Node: // recursively parse a subnode
			hdf->getObjectName(name);
			parseNode(hdf, name, msg);
			break;
		case hdf::Object::Value: // parse and store a variable
			hdf->getObjectName(name);
			u32 tmp;
			if(name == "red" && node == "color") {
				hdf->readInt(tmp);
				msg.color.red = tmp;
			} else if(name == "blue" && node == "color") {
				hdf->readInt(tmp);
				msg.color.blue = tmp;
			} else if(name == "green" && node == "color") {
				hdf->readInt(tmp);
				msg.color.green = tmp;
			} else if(name == "text" && node == "msg") {
				hdf->readString(msg.text);
			} else {
				hdf->error(HDF_LOG_ERROR, "unknown object: " + name);
			}
			break;
		case hdf::Object::NodeEnd: // reached an end of node - exit
			return;
		case hdf::Object::Null:
		default:
			return;
		}
	}
}

int main(int,char**)
{
	// open a file
	io::ReadFile file("../../data/misc/messages.hdf");
	InputFileStream stream(file);
	// create the parser
	Parser* hdf = hdf::createParser(&stream);

	std::vector<Message> msgLog;

	// parse the file until end is reached

	while(hdf->read()) {
		if(hdf->getObjectType() == hdf::Object::Node) {
			std::string name;
			hdf->getObjectName(name);

			// skip unknown node
			if(name != "msg") {
				hdf->error(HDF_LOG_WARNING, "unknown node: " + name);
				hdf->skipNode();
			} else {
				Message msg;
				parseNode(hdf, name, msg);

				msgLog.push_back(msg);
			}
		} else {
			break;
		}
	}

	delete hdf;
}
