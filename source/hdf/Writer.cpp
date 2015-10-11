/*
 * Copyright (C) 2014  absurdworlds
 * Copyright (C) 2015  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <awengine/io/WriteStream.h>
#include <awengine/core/Logger.h>

#include <awengine/hdf/shared.h>
#include "Writer.h"

namespace awrts {
namespace hdf {
hdf::Writer* createWriter(io::WriteStream& outStream)
{
	return new impl_::Writer(outStream);
}

namespace impl_ {
Writer::Writer(io::WriteStream& out)
	: ostream(out), depth(0)
{
}

Writer::~Writer()
{
}

/*! Create a new node and write a header for it. */
bool Writer::startNode(std::string name)
{
	startLine();

	ostream.put('[');
	ostream.put(name);

	++depth;

	endLine();
}

/*! End current (bottom level) node. */
bool Writer::endNode()
{
	if (depth == 0) {
		error(HDF_LOG_ERROR, "‘]’ mismatch");
		return false;
	}

	--depth;

	startLine();

	ostream.put(']');

	endLine();

	return true;
}

/*! Write a value object. */
bool Writer::writeValue(std::string name, hdf::Value value)
{
	if (depth == 0) {
		error(HDF_LOG_ERROR, "field outside node");
		return false;
	}

	startLine();

	ostream.put(name);
	ostream.put(" = ");

	writeValueValue(value);

	endLine();

	return true;
}

// TODO: Implement general-purpose to_string(hdf::Value)
void Writer::writeValueValue(hdf::Value value)
{
	switch (value.getType()) {
	case hdf::Type::Unknown:
		ostream.put("null");
		break;
	case hdf::Type::Integer: {
			i64 i;
			value.get(i);
			ostream.put("int:");
			ostream.put(std::to_string(i));
			break;
		}
	case hdf::Type::Float: {
			f64 f;
			value.get(f);
			ostream.put("float:");
			ostream.put(std::to_string(f));
			break;
		}
	case hdf::Type::Boolean: {
			bool b;
			value.get(b);
			ostream.put("bool:");
			// TODO: does std:: provide same functionality?
			ostream.put(b ? "true" : "false");
			break;
		}
	case hdf::Type::String: {
			std::string s;
			value.get(s);
			ostream.put("string:");
			ostream.put(s);
			break;
		}
	case hdf::Type::Vector2d: {
			  Vector2d<f32> v;
			  value.get(v);
			  ostream.put("vec2:");
			  ostream.put('{');
			  ostream.put(std::to_string(v[0]));
			  ostream.put(",");
			  ostream.put(std::to_string(v[1]));
			  ostream.put('}');
			  break;
		}
	case hdf::Type::Vector3d: {
			  Vector3d<f32> v;
			  value.get(v);
			  ostream.put("vec3:");
			  ostream.put('{');
			  ostream.put(std::to_string(v[0]));
			  ostream.put(",");
			  ostream.put(std::to_string(v[1]));
			  ostream.put(",");
			  ostream.put(std::to_string(v[2]));
			  ostream.put('}');
			  break;
		}
	case hdf::Type::Vector4d: {
			  Vector4d<f32> v;
			  value.get(v);
			  ostream.put("vec4:");
			  ostream.put('{');
			  ostream.put(std::to_string(v[0]));
			  ostream.put(",");
			  ostream.put(std::to_string(v[1]));
			  ostream.put(",");
			  ostream.put(std::to_string(v[2]));
			  ostream.put(",");
			  ostream.put(std::to_string(v[3]));
			  ostream.put('}');
			  break;
		}
	}
}

/*! Write a comment */
void Writer::addComment(std::string comment_text)
{
	startLine();

	ostream.put("//");
	ostream.put(comment_text);

	endLine();
}

/*! Report an error */
void Writer::error(u32 type, std::string msg)
{
	core::Logger::debug("error: " + msg);
}

/*! Set the indentation style for the document */
void Writer::setIndentationStyle(IndentationStyle newStyle)
{
	indentation = newStyle;
}

void Writer::startLine()
{
	if (indentation == IndentationStyle::None)
		return;

	size_t indent_size;
	char indent_char = ' ';

	switch (indentation) {
	case IndentationStyle::Space:
		indent_size = 1;
		break;
	case IndentationStyle::DoubleSpace:
		indent_size = 2;
		break;
	case IndentationStyle::FourSpaces:
		indent_size = 4;
		break;
	case IndentationStyle::EightSpaces:
		indent_size = 8;
		break;
	case IndentationStyle::Tab:
		indent_size = 1;
		indent_char = '\t';
	case IndentationStyle::None:
		break;
	}

	indent_size *= depth;

	std::string indent(indent_char, indent_size);

	ostream.put(indent);
}

void Writer::endLine()
{
	ostream.put('\n');
}

} // namespace impl_
} // namespace io
} // namespace awrts
