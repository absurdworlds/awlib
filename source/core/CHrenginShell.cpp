#include <vector>

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

	std::string arg = command.substr(argStart, argEnd);

	auto cmdIter = commands_.find(command);

	if(cmdIter == commands_.end()) {
		logger_->push("No command found: " + arg);
	} else {
		ICommand* cmd = cmdIter->second;

		argStart = argEnd;
		argEnd = command.find(' ', argStart);
		while(argEnd != std::string::npos) {
			arg = command.substr(argStart, argEnd);
			cmd->pushArg(arg);

			argStart = argEnd;
			argEnd = command.find(' ', argStart);
		}
	}
}

} // namespace core
} // namespace hrengin
