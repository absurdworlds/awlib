/*
 * Copyright (C) 2014-2016  absurdworlds
 * Copyright (C) 2016       Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_utility_argv_parser_h
#define aw_utility_argv_parser_h
#include <string>

#include <aw/utility/utility.h>
#include <aw/types/types.h>
#include <aw/types/optional.h>
namespace aw {
namespace utils {
/*!
 * Command line argument,
 * represents a single option or argument
 */
struct argument {
	argument()
		: type(invalid)
	{ }

	argument(std::string str)
		: type(operand), name(str)
	{ }

	std::string name;

	/*!
	 * List of types of arguments:
	 */
	enum type : u8 {
		//! Invalid argument (unused)
		invalid,
		//! Option ('-o') or ('--option')
		option,
		//! Argument or operand
		operand,
		//! End of arguments delimiter: "--"
		delim
	} type;

	//! Returns true if argument is GNU long option
	bool long_option;
};

/*!
 * Parses program arguments with POSIX syntax, and additionally supports
 * GNU long options.
 *
 * Here is short summary:
 * - Options begin with delimiter '`-`';
 * - Single '`-`' is treated as a non-option argument;
 * - Some options may take arguments;
 * - A space is not necessary between an option and an argument;
 * - Multiple options without arguments can be grouped behind a single '-',
 *   followed by at most one option-argument;
 * - Arguments starting with '`--`' are long options. These must be
 *   separated from other arguments with a space;
 * - Options may appear in different order or multiple times.
 *
 * However, some things are left up to the user of this class:
 * - This parser doesn't check if options consist of alphanumeric characters,
 * - It doesn't support '`--option=argument`' syntax,
 * - Options following '`--`' aren't treated as non-option arguments.
 */
struct AW_UTILS_EXP argv_parser {
	/*!
	 * Create an argument parser
	 * \param argv
	 *      Pointer to the first element of array of
	 *      zero-terminated strings.
	 *      Last element of array must be nullptr.
	 */
	argv_parser(char const* const* argv);

	/*!
	 * Get the next argument from the command line
	 *
	 * \return
	 *     An \a Argument object or \a nullopt in case
	 *     there is no more arguments.
	 */
	optional<argument> parse_argument();

	/*!
	 * Returns either the next parameter, or the rest of
	 * current argument group. If there are no more
	 * arguments left, returns empty string
	 */
	std::string get_param();

private:
	argument next_arg(char const* arg);

	char const* const* argv;
	// Needed to avoid modifying pointers in argv array
	char const* args;
};
} //namespace utils
} //namespace aw
#endif//aw_utility_argv_parser_h
