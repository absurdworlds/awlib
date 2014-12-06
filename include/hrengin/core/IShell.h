/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_IShell_
#define _hrengin_IShell_

#include <string>

#include <hrengin/core/core.h>

#include <hrengin/common/types.h>

namespace hrengin {
class ILogger;
namespace core {
/*!
 * hrengin Shell, intended to be for manipulating game objects via
 * unix-like shell commands
 */
class IShell {
public:
	//! Virtual destructor
	virtual ~IShell()
	{
	}
	
	class ICommand {
	public:
		virtual void pushArg(std::string argument) = 0;
		virtual void execute() = 0;
	};

	virtual void registerCommand(std::string name, ICommand* command) = 0;
	virtual void execute(std::string command) = 0;
};

HR_CORE_EXP IShell* createShell(ILogger* logger);

} // namespace core
} // namespace hrengin
#endif//_hrengin_IShell_
