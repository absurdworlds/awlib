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
bool writer::start_node(string_view name)
{
	ostream.put(get_indent());
	ostream.put('[');
	ostream.put(name);

	++depth;

	end_line();
	return true;
}

/*! End current (bottom level) node. */
bool writer::end_node()
{
	if (depth == 0) {
		error(log::error, "‘]’ mismatch");
		return false;
	}

	--depth;

	ostream.put(get_indent());
	ostream.put(']');

	end_line();

	return true;
}

//! Spell the type of value
string_view spell_type(value const& val)
{
	switch (val.get_type()) {
	case Type::IntegerVector:
	case Type::Integer:
		return "int:";
	case Type::FloatVector:
	case Type::Float:
		return "float:";
	case Type::BooleanVector:
	case Type::Boolean:
		return "bool:";
	case Type::StringVector:
	case Type::String:
		return "string:";
	case Type::Unknown:
	default:
		return {};
	}
}

/*! Write a value object. */
bool writer::write_value(string_view name, value const& val, bool typed)
{
	ostream.put(get_indent());
	ostream.put(name);
	ostream.put(" = ");

	if (typed)
		ostream.put(spell_type(val));

	write_value_value(val);

	end_line();

	return true;
}

void writer::write_value_value(value const& val)
{
	switch (val.get_type()) {
	default:
		ostream.put(to_string(val));
		break;
	case hdf::Type::String:
		ostream.put('"');
		ostream.put(to_string(val));
		ostream.put('"');
		break;
	}
}

/*! Write a comment */
void writer::add_comment(string_view comment)
{
	if (comment.empty())
		return;

	std::string indent = get_indent();
	size_t pos1 = 0;
	size_t pos2;

	do {
		pos2 = comment.find('\n', pos1);
		ostream.put(indent);
		ostream.put("//");
		ostream.put(comment.substr(pos1, pos2 - pos1));
		ostream.put('\n');

		if (pos2 == comment.npos)
			break;

		pos1 = pos2 + 1;
	} while (true);
}

/*! Report an error */
void writer::error(log::level lvl, string_view msg)
{
	if (logger)
		logger->message(lvl, "HDF", msg);
}

/*! Set the indentation style for the document */
void writer::set_indentation_style(IndentationStyle newStyle)
{
	indentation = newStyle;
}

std::string writer::get_indent() const
{
	if (indentation == None)
		return {};

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
		return {};
	return std::string(indent_size, indent_char);
}

void writer::end_line()
{
	ostream.put('\n');
}

} // namespace io
} // namespace aw
