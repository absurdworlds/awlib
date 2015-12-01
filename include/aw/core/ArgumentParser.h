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
	enum Type : u8 {
		//! Option ('-o') or ('--option')
		Option,
		//! Argument or operand
		Arg,
		Operand = Arg,
		Delim
	} type;
	//! Is a long option
	bool longOpt;
	std::string name;
};

//! Used to parse command line arguments passed to the program
class ArgumentParser {
public:
	//! Virtual destructor
	virtual ~ArgumentParser () 
	{
	}

	/*
	 * Get the next argument from the command line
	 *
	 * \param tok Object to hold result
	 * \return
	 * 	Number of remaining arguments if successful,
	 * 	When end is reached, 0 is returned.
	 * 	If error occurs, return value is negative.
	 */
	virtual i32 getNextArgument (Argument& arg) = 0;
};

/*!
 * Create an argument parser
 * \param argv Array of pointers to command line token strings.
 * \note Each string must be null-terminated. Last element of array must be 0.
 */
AW_CORE_EXP ArgumentParser* createArgumentParser (char** argv);

} //namespace core
} //namespace aw
#endif//_aw_ArgumentParser_
