/*
 * Copyright (C) 2014  absurdworlds
 * Copyright (C) 2015  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_fileformat_hdf_writer_h
#define aw_fileformat_hdf_writer_h
#include <string>

#include <aw/fileformat/hdf/export.h>
#include <aw/fileformat/hdf/value.h>

#include <aw/io/WriteStream.h>
#include <aw/log/log.h>
namespace aw {
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

//! Interface for writing HDF files. Supports HDF 1.4.0 format.
struct AW_HDF_EXP Writer {
	//! Create writer outputting to \a out.
	Writer(io::WriteStream& out, log* logger = nullptr)
		: ostream{out}, logger{logger}
	{}

	~Writer() = default;

	/*! Create a new node and write a header for it. */
	bool startNode(std::string name);

	/*! End current (bottom level) node.  */
	bool endNode();

	/*! Write a value object. */
	bool writeValue(std::string name, hdf::Value value, bool typed = true);

	/*! Write a comment */
	void addComment(std::string comment_text);

	/*! Set the indentation style for the document */
	void setIndentationStyle(IndentationStyle style);

private:
	/*! Report an error */
	void error(log::level type, std::string msg);

private:
	void writeValueValue(hdf::Value value);
	void startLine();
	void endLine();

	io::WriteStream& ostream;
	log* logger;
	IndentationStyle indentation = IndentationStyle::DoubleSpace;
	size_t depth = 0;
};
} // namespace io
} // namespace aw
#endif//aw_fileformat_hdf_writer_h
