/*
 * Copyright (C) 2014-2020  absurdworlds
 * Copyright (C) 2015-2020  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_fileformat_hudf_writer_h
#define aw_fileformat_hudf_writer_h
#include <aw/types/string_view.h>

#include <aw/hudf/export.h>
#include <aw/hudf/value.h>

#include <aw/io/WriteStream.h>
#include <aw/log/log.h>
namespace aw::hudf {
/*! List of Writer indentation styles */
enum class indentation_style {
	none,
	tab,
	space,
	double_space,
	four_spaces,
	eight_spaces,
};

//! Interface for writing HuDF files. Supports HuDF 1.4.0 format.
struct AW_HUDF_EXP writer {
	//! Create writer outputting to \a out.
	writer(io::WriteStream& out, log* logger = nullptr)
		: ostream{out}, logger{logger}
	{}

	~writer() = default;

	/*! Create a new node and write a header for it. */
	bool start_node(string_view name);

	/*! End current (bottom level) node.  */
	bool end_node();

	/*! Write a value object. */
	bool write_value(string_view name, const value& val, bool typed = true);

	/*! Write a comment */
	void add_comment(string_view comment_text);

	/*! Set the indentation style for the document */
	void set_indentation_style(indentation_style style);

private:
	/*! Report an error */
	void error(log::level type, string_view msg);

private:
	void write_value_value(const value& val);
	void end_line();
	std::string get_indent() const;

	io::WriteStream& ostream;
	log* logger;
	indentation_style indentation = indentation_style::double_space;
	size_t depth = 0;
};
} // namespace aw::hudf
#endif//aw_fileformat_hudf_writer_h
