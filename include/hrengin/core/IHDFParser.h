/**
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_IHDFReader_
#define _hrengin_IHDFReader_

#include <string>

#include <hrengin/common/api.h>

#include <hrengin/common/Vector3d.h>

#include <hrengin/core/hdf_shared.h>


namespace hrengin {
namespace io {
class ICharacterStream;
}
namespace hdf {
/* Enumeration for objects parsed by HDF parser. */
enum HdfObjectType {
	HDF_OBJ_NULL = 0,
	HDF_OBJ_NODE,
	HDF_OBJ_NODE_END,
	HDF_OBJ_VAL,
	HDF_OBJ_CMD
};


/*! \class IHDFParser
\brief Interface for reading hrengin's HDF files. This parser provides a read-only access to documents in HDF 1.1.1 format.

It can read only in forward mode, it is not able to rewind. The design goal of this parser is to quickly read HDF document without usage of any intermediate data structures.

\see createHDFParser

\exmaple hdf_example.cpp
This is an example of usage of this parser.
*/
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
	virtual void error(hdf::ParserMessage type, std::string msg) = 0;
};

/*! \brief Make an instance of HDF parser.
\param stream
A stream to parse.
\see io::ICharacterStream
*/
HR_CORE_API IHDFParser* createHDFParser(io::ICharacterStream* stream);

} // namespace io
} // namespace hrengin

#endif//_hrengin_IHDFReader_
