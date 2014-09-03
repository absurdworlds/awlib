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
