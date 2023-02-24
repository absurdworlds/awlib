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
namespace aw::utils {
/*!
 * Command line argument,
 * represents a single option or argument
 */
struct argument_info {
	argument_info()
		: type(invalid)
	{ }

	explicit argument_info(std::string str)
		: type(argument), name(str)
	{ }

	argument_info(std::string name, std::string value)
		: type(option), name(name), value(value)
	{ }

	std::string name;
	std::string value;

	/*!
	 * List of types of arguments:
	 */
	enum type : u8 {
		//! Invalid argument (unused)
		invalid,
		//! Option ('-o') or ('--option')
		option,
		//! Positional argument or argument for an option
		argument,
		operand [[deprecated("use argument")]] = argument,
		//! End of arguments delimiter: "--"
		delim
	} type;

	//! Returns true if argument is GNU long option
	bool long_option = false;
};

using argument = argument_info;

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
 * - Options may appear in different order or multiple times;
 * - Supports '`--option=argument`' syntax, but not '`-o=argument`'.
 *
 * However, some things are left up to the user of this class:
 * - This parser doesn't check if options consist only of alphanumeric characters,
 * - Options following '`--`' aren't automatically treated as non-option arguments,
 * - The aprser treats some edge cases '`--=something`' as valid.
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
	 *     An \a argument_info object or \a nullopt in case
	 *     there is no more arguments.
	 */
	optional<argument> parse_argument();

	/*!
	 * Same as \a parse_argument, but always has a parameter.
	 * \return
	 *     An \a argument_info object or \a nullopt in case
	 *     there is no more arguments.
	 */
	optional<argument> parse_option();

	/*!
	 * Returns either the next parameter, or the rest of
	 * current argument group. If there are no more
	 * arguments left, returns empty string
	 */
	std::string get_param();

private:
	argument next_arg(char const* arg);

	char const* const* argv;
	// A group of arguments, like -xvf
	// Needed to avoid modifying pointers in argv array
	char const* arg_group;
};
} //namespace aw::utils
#endif//aw_utility_argv_parser_h
