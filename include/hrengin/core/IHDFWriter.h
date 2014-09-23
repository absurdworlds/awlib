/*
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_IHDFWriter_
#define _hrengin_IHDFWriter_

#include <string>

#include <hrengin/common/api.h>

#include <hrengin/common/Vector3d.h>

namespace hrengin {
namespace hdf {

//! Interface for writing HDF files. Can write documents in HDF 1.1.3 format.
class IHDFWriter {
	virtual ~IHDFWriter() {};

	//! Write a node header, can be used in conjunction with `write*`
	//! to produce a node-value
	virtual bool addNodeHeader(std::string name) = 0;
	virtual bool addNodeEnd() = 0;

	//! Write a `value` object, must be used in conjunction with `write*`
	virtual bool addValue(std::string name) = 0;

	virtual void writeFloat(f32 val) = 0;
	virtual void writeFloat(f64 val) = 0;
	virtual void writeInt(u32 val) = 0;
	virtual void writeInt(i32 val) = 0;
	virtual void writeBool(bool val) = 0;
	virtual void writeString(std::string val) = 0;
	virtual void writeVector3d(Vector3d<f32> val) = 0;

	//! Write a comment
	virtual void addComment(std::string commentText) = 0;

	virtual void error(u32 type, std::string msg) = 0;
};

} // namespace io
} // namespace hrengin

#endif//_hrengin_IHDFWriter_
