/**
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


class IHDFWriter {
	virtual ~IHDFWriter() {};

	virtual bool writeNodeHeader(std::string name) = 0;
	virtual bool writeNodeEnd() = 0;

	virtual void writeFloatValue(std::string name, float val) = 0;
	virtual void writeFloatValue(std::string name, double val) = 0;
	virtual void writeInt(std::string name, u32 val) = 0;
	virtual void writeInt(std::string name, i32 val) = 0;
	virtual void writeBool(std::string name, bool val) = 0;
	virtual void writeString(std::string name, std::string val) = 0;
	virtual void writeVector3d(std::string name, Vector3d<f32> val) = 0;

	virtual void writeComment(std::string commentText) = 0;

	virtual void error(u32 type, std::string msg) = 0;
};


} // namespace io
} // namespace hrengin

#endif//_hrengin_IHDFWriter_
