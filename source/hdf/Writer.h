/*
 * Copyright (C) 2014  absurdworlds
 * Copyright (C) 2015  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_HDF_Writer_impl_
#define _awrts_HDF_Writer_impl_
#include <awrts/hdf/Writer.h>

namespace awrts {
namespace hdf {
namespace impl_ {
//! Implementation of HDF writer. Supports HDF 1.2.0 format.
class Writer : public hdf::Writer {
public:
	Writer(io::WriteStream& out);
	virtual ~Writer();

	/*! Create a new node and write a header for it. */
	virtual bool startNode(std::string name);

	/*! End current (bottom level) node. */
	virtual bool endNode();

	/*! Write a value object. */
	virtual bool writeValue(std::string name, hdf::Value value);

	/*! Write a comment */
	virtual void addComment(std::string comment_text);

	/*! Report an error */
	virtual void error(u32 type, std::string msg);

	/*! Set the indentation style for the document */
	virtual void setIndentationStyle(IndentationStyle newStyle);
private:
	void writeValueValue(hdf::Value value);
	void startLine();
	void endLine();

	io::WriteStream& ostream;
	IndentationStyle indentation;
	size_t depth;
};
} // namespace impl_
} // namespace io
} // namespace awrts
#endif//_awrts_HDF_Writer_impl_
