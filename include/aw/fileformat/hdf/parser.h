/*
 * Copyright (C) 2014-2015  absurdworlds
 * Copyright (C) 2015       Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_fileformat_hdf_reader_h
#define aw_fileformat_hdf_reader_h
#include <string>

#include <aw/fileformat/hdf/value.h>
#include <aw/fileformat/hdf/shared.h>
#include <aw/fileformat/hdf/lexer.h>

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
	Parser(io::input_stream& stream, aw::log* logger = nullptr)
		: lex{stream, logger}
	{}

	~Parser() = default;

	//! Fast-forward to the next object
	bool read();

	/*!
	 * Get next object.
	 * \return
	 *     Returns struct containing object's kind and name.
	 */
	Object getObject();

	/*!
	 * Read value into variable \a out.
	 */
	void readValue(Value& out);

	//! Skip current value
	void skipValue();
	//! Skip current node (with all subnodes)
	void skipNode();

protected:
	void processCommand();

	Value convertValue(Type type);
	Value convertValue(token tok);
	Value parseVector(Type type);
	Value parseVector();

	template <typename T>
	bool parseVector(T& vec, size_t vecsize);

	void message() {  }

	enum class State {
		Idle = 0,
		Object,
		Node,
		Command,
		Value,
		Data,
		Panic
	};

private:
	Lexer lex;
	State state = State::Idle;
	size_t depth = 0;
};
} // namespace io
} // namespace aw
#endif//aw_fileformat_hdf_reader_h
