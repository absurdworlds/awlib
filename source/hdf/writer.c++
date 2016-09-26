/*
 * Copyright (C) 2014  absurdworlds
 * Copyright (C) 2015  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <aw/fileformat/hdf/writer.h>

namespace aw {
namespace hdf {
/*! Create a new node and write a header for it. */
bool Writer::startNode(std::string name)
{
	startLine();

	ostream.put('[');
	ostream.put(name);

	++depth;

	endLine();
	return true;
}

/*! End current (bottom level) node. */
bool Writer::endNode()
{
	if (depth == 0) {
		error(log::error, "‘]’ mismatch");
		return false;
	}

	--depth;

	startLine();

	ostream.put(']');

	endLine();

	return true;
}

//! Spell the type of value
std::string spellType(hdf::Value value)
{
	switch (value.getType()) {
	case hdf::Type::Unknown:
		return {};
	case hdf::Type::Enum:
		return {"enum:"};
	case hdf::Type::Integer:
		return {"int:"};
	case hdf::Type::Float:
		return {"float:"};
	case hdf::Type::Boolean:
		return {"bool:"};
	case hdf::Type::String:
		return {"string:"};
	case hdf::Type::Vector2d:
		return {"vec2:"};
	case hdf::Type::Vector3d:
		return {"vec3:"};
	case hdf::Type::Vector4d:
		return {"vec4:"};
	}
}

/*! Write a value object. */
bool Writer::writeValue(std::string name, hdf::Value value, bool typed)
{
	if (depth == 0) {
		error(log::error, "field outside node");
		return false;
	}

	startLine();

	ostream.put(name);
	ostream.put(" = ");

	if (typed)
		ostream.put(spellType(value));

	writeValueValue(value);

	endLine();

	return true;
}

void Writer::writeValueValue(hdf::Value value)
{
	switch (value.getType()) {
	default:
		ostream.put(to_string(value));
		break;
	case hdf::Type::String:
		ostream.put('"');
		ostream.put(to_string(value));
		ostream.put('"');
		break;
	case hdf::Type::Vector2d:
		ostream.put(to_string(value));
		break;
	case hdf::Type::Vector3d:
		ostream.put("vec3:");
		ostream.put(to_string(value));
		break;
	case hdf::Type::Vector4d:
		ostream.put("vec4:");
		ostream.put(to_string(value));
		break;
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
void Writer::error(log::level lvl, std::string msg)
{
	if (logger)
		logger->message(lvl, "HDF", msg);
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

	size_t indent_size = 0;
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

	if (indent_size == 0)
		return;

	std::string indent(indent_size, indent_char);

	ostream.put(indent);
}

void Writer::endLine()
{
	ostream.put('\n');
}

} // namespace io
} // namespace aw
