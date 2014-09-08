/**
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _hrengin_CHrenginShell_
#define _hrengin_CHrenginShell_

#include <map>

#include <hrengin/core/ILogger.h>
#include <hrengin/core/IShell.h>

namespace hrengin {
namespace core {

/*
   hrengin Shell, intended to be for manipulating the game via unix-like shell
   commands.

   This interface is temporary, and will be repalced by a more advanced one as
   soon as virtual filesystem is ready (IFilesystem)
 */
class CHrenginShell : public IShell{
public:
	CHrenginShell(ILogger* logger);

	virtual ~CHrenginShell() {};

	virtual void registerCommand(std::string name, ICommand* command)
	{
		auto cmdIter = commands_.find(name);

		if(cmdIter == commands_.end()) {
			commands_[name] = command;
		}
	}

	virtual void execute(std::string command);
private:
	std::map<std::string, ICommand*> commands_;

	ILogger* logger_;
};

IShell* createShell(ILogger* logger)
{
	return new CHrenginShell(logger);
}

} // namespace core
} // namespace hrengin


#endif//_hrengin_CHrenginShell_
