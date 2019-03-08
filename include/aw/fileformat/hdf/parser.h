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
#include <aw/fileformat/hdf/lexer.h>

#include <aw/io/input_stream.h>

namespace aw {
namespace hdf {
inline namespace v1 {
/*!
 * Object returned by awhdf parser
 */
struct object {
	enum {
		/*! No object, represents EOF */
		null,
		/*! Start of a [node */
		node,
		/*! End of a node ] */
		end,
		/*! Value */
		value,
	} kind = null;
	std::string name;
	struct value val;

	/*! Returns true if this is a real object. */
	explicit operator bool() const
	{
		return in(kind, node, value);
	}

};

using object_kind = decltype(object::kind);

/*!
 * Provides simple low-level interface for reading an awhdf files.
 *
 * For an usage example, see 'tests/reader.c++'.
 */
struct parser {
	parser(io::input_stream& stream, aw::log* log = nullptr)
		: lex{stream, log}
	{}

	~parser() = default;

	//! Read an object
	object read();

	/*!
	 * Read an object
	 * \return
	 * True if something was read, false otherwise.
	 */
	bool read(object& obj)
	{
		obj = read();
		return obj.kind != object::null;
	}

	//! Skip current node
	void skip_node();

protected:
	friend struct object;

	void processCommand();

	value read_value();

	template <typename T>
	value parse_value();
	value parse_value(token id);
	value deduce_value(token tok);

	void skip_vector();

	template <typename T>
	std::vector<T> parse_vector(token::position beg);
	value parse_vector(token id);
	value deduce_vector(token::position beg);

private:
	lexer lex;
	size_t depth = 0;
};
} // inline namespace v1
} // namespace hdf
} // namespace aw
#endif//aw_fileformat_hdf_reader_h
