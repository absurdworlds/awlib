/*
 * Copyright (C) 2014  absurdworlds
 * Copyright (C) 2015  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <aw/hudf/writer.h>

namespace aw::hudf {
/*! Create a new node and write a header for it. */
bool writer::start_node(string_view name)
{
	ostream << get_indent();
	ostream << '[';
	ostream << name;

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

	ostream << get_indent();
	ostream << ']';

	end_line();

	return true;
}

//! Spell the type of value
string_view spell_type(const value& val)
{
	switch (val.get_type()) {
	case type::integer_vector:
	case type::integer:
		return "int:";
	case type::float_vector:
	case type::floating_point:
		return "float:";
	case type::boolean_vector:
	case type::boolean:
		return "bool:";
	case type::string_vector:
	case type::string:
		return "string:";
	case type::unknown:
	default:
		return {};
	}
}

/*! Write a value object. */
bool writer::write_value(string_view name, value const& val, bool typed)
{
	write_token_sep();
	ostream << get_indent();
	ostream << name;
	ostream << '=';

	if (typed)
		ostream << spell_type(val);

	write_value_value(val);

	end_line();

	return true;
}

void writer::write_value_value(const value& val)
{
	switch (val.get_type()) {
	default:
		ostream << to_string(val);
		break;
	case type::string:
		ostream << '"';
		ostream << to_string(val);
		ostream << '"';
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
		// Not using end_line here so that
		// comments don't eat up the data
		// TODO: make end_line() smarter
		pos2 = comment.find('\n', pos1);
		if (!line_breaks)
			ostream << '\n';
		ostream << indent;
		ostream << "//";
		ostream << comment.substr(pos1, pos2 - pos1);
		ostream << '\n';

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
void writer::set_indentation_style(indentation_style newStyle)
{
	indentation = newStyle;
}

std::string writer::get_indent() const
{
	if (indentation == indentation_style::none)
		return {};

	size_t indent_size = 0;
	char indent_char = ' ';

	switch (indentation) {
	case indentation_style::none:
		break;
	case indentation_style::space:
		indent_size = 1;
		break;
	case indentation_style::double_space:
		indent_size = 2;
		break;
	case indentation_style::four_spaces:
		indent_size = 4;
		break;
	case indentation_style::eight_spaces:
		indent_size = 8;
		break;
	case indentation_style::tab:
		indent_size = 1;
		indent_char = '\t';
	}

	indent_size *= depth;

	if (indent_size == 0)
		return {};
	return std::string(indent_size, indent_char);
}

void writer::end_line()
{
	if (line_breaks)
		ostream.put('\n');
	else
		token_sep = true;
}

void writer::write_token_sep()
{
	if (token_sep) {
		ostream.put(' ');
		token_sep = false;
	}
}

} // namespace aw::hudf
