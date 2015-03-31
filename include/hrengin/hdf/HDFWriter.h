/*
 * Copyright (C) 2014  absurdworlds
 * Copyright (C) 2015  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_HDFWriter_
#define _hrengin_HDFWriter_
#include <string>

#include <hrengin/hdf/hdf.h>
#include <hrengin/hdf/Value.h>
namespace hrengin {
namespace hdf {
//! Interface for writing HDF files. Supports HDF 1.2.0 format.
class Writer {
	virtual ~Writer() {};

	/*! Create a new node and write a header for it. */
	virtual bool startNode(std::string name) = 0;

	/*! End current (bottom level) node.  */
	virtual bool endNode() = 0;

	/*! Write a value object. */
	virtual bool writeValue(std::string name, hdf::Value value) = 0;

	/*! Write a comment */
	virtual void addComment(std::string comment_text) = 0;

	/*! Report an error */
	virtual void error(u32 type, std::string msg) = 0;
};

} // namespace io
} // namespace hrengin
#endif//_hrengin_HDFWriter_
