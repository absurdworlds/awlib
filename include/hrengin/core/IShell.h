#ifndef _hrengin_IShell_
#define _hrengin_IShell_

#include <string>

#include <hrengin/common/api.h>
#include <hrengin/common/types.h>

namespace hrengin {
class ILogger;
namespace core {

/*
   hrengin Shell, intended to be for manipulating game objects via
   unix-like shell commands
 */
class IShell {
public:
	virtual ~IShell() {};
	
	class ICommand {
	public:
		virtual void pushArg(std::string argument) = 0;
		virtual void execute() = 0;
	};

	virtual void registerCommand(std::string name, ICommand* command) = 0;
	virtual void execute(std::string command) = 0;
};

HR_CORE_API IShell* createShell(ILogger* logger);

} // namespace core
} // namespace hrengin


#endif//_hrengin_IShell_