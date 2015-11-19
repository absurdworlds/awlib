/*
 * Copyright (C) 2014  absurdworlds
 * Copyright (C) 2015  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_HDF_Writer_
#define _awrts_HDF_Writer_
#include <string>

#include <awengine/hdf/hdf.h>
#include <awengine/hdf/Value.h>
namespace awrts {
namespace io {
class WriteStream;
}
namespace hdf {
/*! List of Writer indentation styles */
enum IndentationStyle {
	Tab,
	Space,
	DoubleSpace,
	FourSpaces,
	EightSpaces,
	None
};

//! Interface for writing HDF files. Supports HDF 1.2.0 format.
class Writer {
public:
	virtual ~Writer() = default;

	/*! Create a new node and write a header for it. */
	virtual bool startNode(std::string name);

	/*! End current (bottom level) node.  */
	virtual bool endNode();

	/*! Write a value object. */
	virtual bool writeValue(std::string name, hdf::Value value);

	/*! Write a comment */
	virtual void addComment(std::string comment_text);

	/*! Report an error */
	virtual void error(u32 type, std::string msg);

	/*! Set the indentation style for the document */
	virtual void setIndentationStyle(IndentationStyle style);
private:
	void writeValueValue(hdf::Value value);
	void startLine();
	void endLine();

	io::WriteStream& ostream;
	IndentationStyle indentation;
	size_t depth;
};
} // namespace io
} // namespace awrts
#endif//_awrts_HDF_Writer_
