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

#include <aw/core/core.h>
#include <aw/common/types.h>

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
		Invalid,
		//! Option ('-o') or ('--option')
		Option,
		//! Argument or operand
		Operand,
		//! End of arguments delimiter: "--"
		Delim
	} type;

	std::string name;

	//! Returns true if it is a long option
	bool longOpt() const
	{
		return type == Option && name.size() == 1;
	}
};

//! Used to parse command line arguments passed to the program
class AW_CORE_EXP ArgumentParser {
public:
	/*!
	 * Create an argument parser
	 * \param argv
	 *     Array of pointers to command line token strings.
	 *     (e.g. one that is passed to `main()`)
	 * \note
	 *     Each string and array itself must be null-terminated.
	 */
	ArgumentParser(char const* const* argv);

	/*
	 * Get the next argument from the command line
	 *
	 * \param tok Object to hold result
	 * \return
	 * 	Number of remaining arguments if successful,
	 * 	When end is reached, 0 is returned.
	 * 	If error occurs, return value is negative.
	 */
	opt<Argument> parseArgument();
private:
	Argument nextArg(char const* arg);

	char const* const* argv;
	// Prevent modifying pointers
	char const* args;
};
} //namespace core
} //namespace aw
#endif//_aw_ArgumentParser_
