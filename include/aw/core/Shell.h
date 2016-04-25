/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_Shell_
#define _aw_Shell_
#include <string>

#include <aw/core/core.h>

#include <aw/common/types.h>

namespace aw {
class Logger;
namespace core {
/*!
 * aw Shell, intended to be for manipulating game objects via
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

AW_CORE_EXP Shell* createShell(Logger* logger);

} // namespace core
} // namespace aw
#endif//_aw_Shell_
