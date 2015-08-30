/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _awrts_Shell_
#define _awrts_Shell_

#include <string>

#include <awrts/core/core.h>

#include <awrts/common/types.h>

namespace awrts {
class Logger;
namespace core {
/*!
 * awrts Shell, intended to be for manipulating game objects via
 * unix-like shell commands
 */
class Shell {
public:
	//! Virtual destructor
	virtual ~Shell()
	{
	}

	class Command {
	public:
		virtual void pushArg(std::string argument) = 0;
		virtual void execute() = 0;
	};

	virtual void registerCommand(std::string name, Command* command) = 0;
	virtual void execute(std::string command) = 0;
};

HR_CORE_EXP Shell* createShell(Logger* logger);

} // namespace core
} // namespace awrts
#endif//_awrts_Shell_
