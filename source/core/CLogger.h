#ifndef _hrengin_CLogger_
#define _hrengin_CLogger_

#include <vector>

#include <hrengin/core/ILogger.h>

namespace hrengin {

class CLogger : public ILogger {
public:
	CLogger();
	virtual ~CLogger();

	virtual void push(std::string msg);
	virtual void addLog(ILogBook* log);
private:
	std::vector<ILogBook*> logs_;
};

} // namespace hrengin

#endif//_hrengin_CLogger_
