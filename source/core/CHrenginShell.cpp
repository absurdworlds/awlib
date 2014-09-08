/**
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
#include <vector>
#include <algorithm>

#include "CHrenginShell.h"

namespace hrengin {
namespace core {

CHrenginShell::CHrenginShell(ILogger* logger)
	: logger_(logger)
{
	
}

void CHrenginShell::execute(std::string command)
{
	typedef std::string::size_type size_type;
	if(command == "") {
		return;
	}

	logger_->push("$ " + command);

	size_type argStart = 0;
	size_type argEnd = command.find(' ', argStart);


	if(argEnd == std::string::npos) {
		argEnd = command.length();
	}

	std::string arg = command.substr(argStart, argEnd-argStart);

	auto cmdIter = commands_.find(arg);

	if(cmdIter == commands_.end()) {
		logger_->push("No command found: " + arg);
	} else {
		ICommand* cmd = cmdIter->second;

		while(argEnd != std::string::npos) {
			argStart = argEnd+1;
			argEnd = command.find(' ', argStart);

			arg = command.substr(argStart, argEnd-argStart);

			std::remove_if(arg.begin(), arg.end(), isspace);

			if(arg != "") {
				cmd->pushArg(arg);
			} else {
				break;
			}
		}

		cmd->execute();
	}
}

} // namespace core
} // namespace hrengin
