/*
 * Copyright (C) 2014-2015  absurdworlds
 * Copyright (C) 2015       Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_HDFReader_h
#define aw_HDFReader_h
#include <string>

#include <aw/math/vector3d.h>

#include <aw/hdf/hdf.h>
#include <aw/hdf/Value.h>
#include <aw/hdf/shared.h>

#include <aw/io/input_stream.h>

namespace aw {
namespace hdf {
/*!
 * Object returned by HDF parser
 */
struct Object {
	enum Kind {
		Null = 0,
		Node,
		NodeEnd,
		Value,
		Directive
	};

	Object(Kind type)
		: type(type)
	{ }

	Object(Kind type, std::string val)
		: type(type), name(val)
	{ }

	Kind type;
	std::string name;
};

/*!
 * \class Parser
 * \brief Interface for reading aw's HDF files. This parser provides a read-only access to documents in HDF 1.1.1 format.
 *
 * It can read only in forward mode, it is not able to rewind. The design goal of this parser is to quickly read HDF document without usage of any intermediate data structures.
 *
 * \see createParser
 * Also, see an example in 'examples' directory
*/
struct Parser {
	virtual ~Parser() = default;

	//! Fast-forward to the next object
	virtual bool read() = 0;

	/*!
	 * Get next object.
	 * \return
	 *     Returns struct containing object's kind and name.
	 */
	virtual Object getObject() = 0;

	/*!
	 * Read value into variable \a out.
	 */
	virtual void readValue(Value& out) = 0;

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
	virtual void error(size_t pos, std::string msg) = 0;
};

/*!
 * \brief Make an instance of HDF parser.
 * \param stream Stream to parse.
 * \see io::CharacterStream
*/
AW_HDF_EXP Parser* createParser(io::input_stream& stream);
} // namespace io
} // namespace aw
#endif//aw_HDFReader_h
