#include <fstream>
#include <string>
#include <vector>

#include <hrengin/hdf/IHDFParser.h>

using namespace hrengin;
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
void parseNode(IHDFParser* hdf, std::string node, Message& msg)
{
	// any object must be read strictly in this order
	while(hdf->read()) {
		HdfObjectType type = hdf->getObjectType();
		std::string name;

		hdf->getObjectName(name);

		switch(type) {
		case HDF_OBJ_NODE: // recursively parse a subnode
			parseNode(hdf, name, msg);
			break;
		case HDF_OBJ_VAL: // parse and store a variable
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
		case HDF_OBJ_NODE_END: // reached an end of node - exit
			return;
		case HDF_OBJ_NULL:
		default:
			return;
		}
	}
}

int main(int,char**)
{
	// open a file
	IReadFile* file = openReadFile("../data/misc/messages.hdf");
	IBufferedStream *stream = io::createBufferedStream(file);
	// create the parser
	IHDFParser* hdf = createHDFParser(stream);

	std::vector<Message> msgLog;

	// parse the file until end is reached

	while(hdf->read()) {
		if(hdf->getObjectType() == HDF_OBJ_NODE) {
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
