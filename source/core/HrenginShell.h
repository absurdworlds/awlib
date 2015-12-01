/*
 * Copyright (C) 2014  absurdworlds
 *
 * License LGPLv3-only:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef _aw_HrenginShell_
#define _aw_HrenginShell_
#include <map>

#include <aw/core/Logger.h>
#include <aw/core/Shell.h>

namespace aw {
namespace core {

/*
 * hrengin Shell, intended to be for manipulating the game via unix-like shell
 * commands.
 *
 * This interface is temporary, and will be repalced by a more advanced one as
 * soon as virtual filesystem is ready (IFilesystem)
 */
class HrenginShell : public Shell {
public:
	HrenginShell(Logger* logger);

	virtual ~HrenginShell() {};

	virtual void registerCommand(std::string name, Command* command)
	{
		auto cmdIter = commands_.find(name);

		if(cmdIter == commands_.end()) {
			commands_[name] = command;
		}
	}

	virtual void execute(std::string command);
private:
	std::map<std::string, Command*> commands_;

	Logger* logger_;
};

Shell* createShell(Logger* logger)
{
	return new HrenginShell(logger);
}

} // namespace core
} // namespace aw
#endif//_aw_HrenginShell_
