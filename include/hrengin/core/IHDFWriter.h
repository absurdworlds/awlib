#ifndef _hrengin_IHDFWriter_
#define _hrengin_IHDFWriter_

#include <string>

#include <hrengin/common/api.h>

#include <hrengin/common/Vector3d.h>


namespace hrengin {
namespace hdf {

enum HDFIndentation {
	HDF_INDENT_TAB,
	HDF_INDENT_SPACE,
	HDF_INDENT_DOUBLE_SPACE,
	HDF_INDENT_QUAD_SPACE,
	HDF_INDENT_OCTAL_SCAPE
};

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
