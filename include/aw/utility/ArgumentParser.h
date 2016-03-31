/*
 * Copyright (C) 2014-2015  absurdworlds
 * Copyright (C) 2015       Hedede <hededrk@gmail.com>
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_ArgumentParser_
#define _aw_ArgumentParser_
#include <string>

#include <aw/utility/utility.h>
#include <aw/types/types.h>
namespace aw {
namespace core {
/*!
 * Command line argument,
 * represents a single option or argument
 */
struct Argument {
	Argument()
		: type(Invalid)
	{ }

	Argument(std::string str)
		: type(Operand),
		  name(str)
	{ }

	/*!
	 * List of types of arguments:
	 */
	enum Type : u8 {
		//! Invalid argument (unused)
		Invalid,
		//! Option ('-o') or ('--option')
		Option,
		//! Argument or operand
		Operand,
		//! End of arguments delimiter: "--"
		Delim
	} type;

	std::string name;

	//! Returns true if Argument is GNU long option
	bool longOpt;
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
class AW_UTILS_EXP ArgumentParser {
public:
	/*!
	 * Create an argument parser
	 * \param argv
	 *      Pointer to the first element of array of
	 *      zero-terminated strings.
	 *      Last element of array msut be nullptr.
	 */
	ArgumentParser(char const* const* argv);

	/*!
	 * Get the next argument from the command line
	 *
	 * \return
	 *     An \a Argument object or \a nullopt in case
	 *     there is no more arguments.
	 */
	opt<Argument> parseArgument();

	/*!
	 * Returns either the next parameter, or the rest of
	 * current argument group. If there are no more
	 * arguments left, returns empty string
	 */
	std::string getParam();
private:
	Argument nextArg(char const* arg);

	char const* const* argv;
	// Needed to avoid modifying pointers in argv array
	char const* args;
};
} //namespace core
} //namespace aw
#endif//_aw_ArgumentParser_
