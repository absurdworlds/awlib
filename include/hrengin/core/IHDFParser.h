#ifndef _hrengin_IHDFParser_
#define _hrengin_IHDFParser_

#include <hrengin/common/api.h>

#include <hrengin/common/Vector3d.h>

#include <string>

namespace hrengin {
namespace io {

class IReadFile;
class ICharacterStream;

/* Enumeration for objects parsed by HDF parser. */
enum HdfObjectType {
	HDF_OBJ_NULL = 0,
	HDF_OBJ_NODE,
	HDF_OBJ_NODE_END,
	HDF_OBJ_VAL,
	HDF_OBJ_CMD
};

/* Enumeration for parser log messages */
enum HdfParserMessage {
	HDF_ERR_NOTICE,
	HDF_ERR_WARNING,
	HDF_ERR_ERROR
};

/* 
# HDF parser
## Description
Interface for reading hrengin's HDF files. This parser provides a read-only access to documents in HDF 1.1.1 format.

It can read only in forward mode, it is not able to rewind. The design goal of this parser is to quickly read HDF document without usage of any intermediate data structures.

## Usage
To create a HDF parser use a factory function
	IHDFParser* createHDFParser(IReadFile* file);

The code below provides an example of reading this structure:
	
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

### Example code
	#include <string>
	#include <vector>

	#include <hrengin/platform/IReadFile.h>
	#include <hrengin/core/IHDFParser.h>

	using namespace hrengin;
	using namespace io;

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
		// open the file and parser
		IReadFile* file = openReadFile("file.hdf");
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
*/

/* Interface for reading hrengin's HDF files. This parser provides a read-only access to documents in HDF 1.1.1 format. */
class IHDFParser {
public:
	virtual ~IHDFParser() {};

	/* fast-forward to the next object */
	virtual bool read() = 0;

	/* read the object's type
	   return: the object type or 0 (HDF_OBJ_NULL) in case of failure */
	virtual HdfObjectType getObjectType() = 0;
	
	/* read the object's name
	   arg name: output of the function
	   return: name of the object or empty string in case of failure */
	virtual void getObjectName(std::string& name) = 0;

	/* read the value of the variable
	   param val: output of the function
	   return: formatted value */
	virtual void readFloat(float& val) = 0;
	virtual void readFloat(double& val) = 0;
	virtual void readInt(u32& val) = 0;
	virtual void readInt(i32& val) = 0;
	virtual void readBool(bool& val) = 0;
	virtual void readString(std::string& val) = 0;
	//virtual void readString(char* val) = 0;
	virtual void readVector3d(Vector3d<f32>& val) = 0;

	/* skip current value or node (with all subnodes) */
	virtual void skipValue() = 0;
	virtual void skipNode() = 0;

	/* add message to the parser's error log
	   HDF_ERR_NOTICE — an unimportant message
	   HDF_ERR_WARNING — warning, non-critical error
	   HDF_ERR_ERROR — critical error, stops the parsing*/
	virtual void error(HdfParserMessage type, std::string msg) = 0;
};

/* Make an instance of HDF parser */
HR_CORE_API IHDFParser* createHDFParser(ICharacterStream* stream);

} // namespace io
} // namespace hrengin

#endif//_hrengin_IHDFParser_
