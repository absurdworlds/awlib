/*
 * Copyright (C) 2014-2015  absurdworlds
 * Copyright (C) 2015       Hedede <hededrk@gmail.com>
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_ArgParser_
#define _hrengin_ArgParser_

#include <string>

#include <hrengin/core/core.h>
#include <hrengin/common/types.h>

namespace hrengin {
namespace core {
/*!
 * Command line argument,
 * represents a single option or argument
 */
struct ClineArg {
	enum Type : u8 {
		//! Short option ('-o')
		Option,
		//! Argument or operand
		Argument,
		Operand = Argument,
		Delim
	} type;
	//! Is a long option
	bool longOpt;
	std::string name;
};

//! Used to parse command line arguments passed to the program
class ArgParser {
public:
	//! Virtual destructor
	virtual ~ArgParser () 
	{
	}

	/*
	 * Get the next argument from the command line
	 *
	 * \param tok Object to hold result
	 * \return
	 * 	Number of remaining arguments if successful,
	 * 	When end is reached, 0 is returned.
	 * 	If error occurs, return value is -`.
	 */
	virtual i32 getNextArgument (ClineArg& arg) = 0;
};

/*!
 * Create an argument parser
 * \param argv Array of pointers to command line token strings.
 * \note Each string must be null-terminated. Last element of array must be 0.
 */
HR_CORE_EXP ArgParser* createArgParser (char** argv);

} //namespace core
} //namespace hrengin
#endif//_hrengin_ArgParser_
