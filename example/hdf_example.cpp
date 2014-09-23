#include <string>
#include <vector>

#include <hrengin/io/IReadFile.h>
#include <hrengin/core/IHDFParser.h>

using namespace hrengin;
using namespace io;

/* Code below provides an example of parsing this document:
\code
	!hdf_version "1.1.1"
	[msg [color 
		red = 100
		blue = 200
		green = 200]
		text = "Starting the endine"]
	[msg [color 
		red = 80
		blue = 80
		green = 240]
		text = "Success!"]
	[msg [color 
		red = 80
		green = 80
		blue = 240]
		text = "Reading config..."]
\endcode
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
		std::string name

		hdf->getObjectName(name);

		switch(type) {
		case HDF_OBJ_NODE: // recursively parse a subnode
			parseNode(hdf, name, msg);
			break;
		case HDF_OBJ_VAL: // parse and store a variable 
			if(name == "red" && node == "color") {
				hdf->readInt(msg.color.red);
			} else if(name == "blue" && node == "color") {
				hdf->readInt(msg.color.red);
			} else if(name == "green" && node == "color") {
				hdf->readInt(msg.color.red);
			} else if(name == "text" && node == "msg") {
				hdf->readString(msg.text);
			} else {
				hdf->error(HDF_ERR_ERROR, "unknown object: " + name);
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

void main()
{
	// open a file
	IReadFile* file = openReadFile("file.hdf");
	// create the parser
	IHDFParser* hdf = createHDFParser(file);

	std::vector<Message> msgLog;

	// parse the file until end is reached

	while(hdf->read()) {
		if(hdf->getObjectType() == HDF_OBJ_NODE)) {
			std::string name;
			hdf->getObjectName(name);

			// skip unknown node
			if(name != "msg") {
				hdf->error(HDF_ERR_WARNING, "unknown node: " + name);
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
	delete file;
}