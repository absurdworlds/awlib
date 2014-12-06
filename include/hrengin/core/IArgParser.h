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
namespace io {
//! Used to parse command line arguments passed to the program
class IArgParser {
public:
	//! Type of token
	enum TokenType {
		//! Short option ('-o')
		Option,
		//! Long option ('--option')
		LongOpt,
		//! Argument or operand
		Argument,
		Operand = Argument
	};

	//! Command line token, represents a single option or argument
	struct Token {
		TokenType type;
		std::string name;
	};

	//! Virtual destructor
	virtual ~IArgParser () 
	{
	}

	/* Get a single token
	 * \param tok Object to hold result
	 * \return >0 if successful, 0 upon reaching end
	 */
	virtual i32 getToken (IArgParser::Token& tok) = 0;
};

/*! Create an argument parser
 * \param argv Array of argument strings.
 * Each argument must be null-terminated.
 * Last element of array must be 0.
 */
HR_CORE_EXP IArgParser* createArgParser (char** argv);

} //namespace io
} //namespace hrengin
#endif//_hrengin_IArgParser_
