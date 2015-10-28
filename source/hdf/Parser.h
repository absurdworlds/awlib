/*
 * Copyright (C) 2014-2105  absurdworlds
 * Copyright (C) 2015       Hedede <hededrk@gmail.com>
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_hdf_Parser_impl_
#define _awrts_hdf_Parser_impl_
#include <string>
#include <vector>

#include <awengine/hdf/Value.h>
#include <awengine/hdf/Parser.h>

#include "Lexer.h"

namespace awrts {
namespace hdf {
namespace impl_ {
class Parser : public hdf::Parser {
public:
	Parser(io::InputStream& stream);
	virtual ~Parser() = default;

	virtual void skipNode();
	virtual void skipValue();

	virtual bool read();

	virtual Object getObject();

	/*!
	 * Read value into variable \a out.
	 */
	virtual void readValue(Value& out);

	void error(size_t pos, std::string msg);
private:
	void processCommand();

	Value convertValue(Type type);
	Value convertValue(Token tok);
	Value parseVector(Type type);
	Value parseVector();

	template <typename T>
	bool parseVector(T& vec, size_t vecsize);

	Lexer lex;

	enum class State {
		Idle = 0,
		Object,
		Node,
		Command,
		Value,
		Data,
		Panic
	} state;

	size_t depth;
	std::vector<std::string> errors;
};
} // namespace impl_
} // namespace io
} // namespace awrts
#endif//_awrts_hdf_Parser_impl_
