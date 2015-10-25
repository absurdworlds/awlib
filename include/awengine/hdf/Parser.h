/*
 * Copyright (C) 2014-2015  absurdworlds
 * Copyright (C) 2015       Hedede <hededrk@gmail.com>
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_HDFReader_
#define _awrts_HDFReader_
#include <string>

#include <awengine/math/Vector3d.h>

#include <awengine/hdf/hdf.h>
#include <awengine/hdf/shared.h>

namespace awrts {
namespace io {
class InputStream;
}

namespace hdf {
/*!
 * Enumeration of objects returned by HDF parser.
 */
enum class Object {
	Null = 0,
	Node,
	NodeEnd,
	Value,
	Directive
};

/*!
 * \class Parser
 * \brief Interface for reading awrts's HDF files. This parser provides a read-only access to documents in HDF 1.1.1 format.
 * 
 * It can read only in forward mode, it is not able to rewind. The design goal of this parser is to quickly read HDF document without usage of any intermediate data structures.
 * 
 * \see createParser
 * Also, see an example in 'examples' directory
*/
class Parser {
public:
	virtual ~Parser() = default;

	//! Fast-forward to the next object
	virtual bool read() = 0;

	/*! Read the object's type
	 * \return
	 *     The object type or 0 (HDF_OBJ_NULL) in case of failure
	 */
	virtual Object getObjectType() = 0;
	
	/*! Read the object's name
	 * \param name
	 *     Gets set to the name of the object or empty string in
	 * case of failure
	 */
	virtual void getObjectName(std::string& name) = 0;

	/*! Read the value of the variable
	 * \param val
	 *     Variable to output to
	 */
	virtual void readFloat(float& val) = 0;
	virtual void readFloat(double& val) = 0;
	virtual void readInt(u32& val) = 0;
	virtual void readInt(i32& val) = 0;
	virtual void readBool(bool& val) = 0;
	virtual void readString(std::string& val) = 0;
	//virtual void readString(char* val) = 0;
	virtual void readVector3d(Vector3d<f32>& val) = 0;

	//! Skip current value
	virtual void skipValue() = 0;
	//! Skip current node (with all subnodes)
	virtual void skipNode() = 0;

	/*!
	 * Add message to the parser's error log
	 * HDF_ERR_NOTICE - an unimportant message
	 * HDF_ERR_WARNING - warning, non-critical error
	 * HDF_ERR_ERROR - critical error, stops the parsing
	 */
	virtual void error(hdf::ParserMessage type, std::string msg) = 0;
};

/*!
 * \brief Make an instance of HDF parser.
 * \param stream Stream to parse.
 * \see io::CharacterStream
*/
AW_HDF_EXP Parser* createParser(io::InputStream* stream);
} // namespace io
} // namespace awrts
#endif//_awrts_HDFReader_
