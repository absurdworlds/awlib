/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_IArgParser_
#define _hrengin_IArgParser_

#include <string>

#include <hrengin/core/core.h>
#include <hrengin/common/types.h>

namespace hrengin {
namespace core {
/*!
 * Command-line argument,
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
class IArgParser {
public:
	//! Virtual destructor
	virtual ~IArgParser () 
	{
	}

	/* Get a single token
	 * \param tok Object to hold result
	 * \return >0 if successful, 0 upon reaching end
	 */
	virtual i32 getToken (ClineArg& tok) = 0;
};

/*!
 * Create an argument parser
 * \param argv Array of pointers to command line token strings.
 * \note Each string must be null-terminated. Last element of array must be 0.
 */
HR_CORE_EXP IArgParser* createArgParser (char** argv);

} //namespace core
} //namespace hrengin
#endif//_hrengin_IArgParser_
