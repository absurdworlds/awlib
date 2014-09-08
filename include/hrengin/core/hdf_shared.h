/**
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_hdf_shared_
#define _hrengin_hdf_shared_

namespace hrengin {
namespace hdf {

/* Enumeration of possible HDF value types */
enum class Type {
	Integer,
	Float,
	Boolean,
	String,
	Vector2d,
	Vector3d,
	Unknown
};

/* Enumeration for selecting writer indentation style */
enum Indentation {
	HDF_INDENT_TAB,
	HDF_INDENT_SPACE,
	HDF_INDENT_DOUBLE_SPACE,
	HDF_INDENT_QUAD_SPACE,
	HDF_INDENT_OCTAL_SCAPE,
	HDF_INDENT_NONE
};

/* Enumeration for parser log messages */
enum ParserMessage {
	HDF_LOG_NOTICE,
	HDF_LOG_WARNING,
	HDF_LOG_ERROR
};

} // namespace hdf
} // namespace hrengin

#endif//_hrengin_hdf_shared_
