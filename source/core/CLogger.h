/**
   Copyright (C) 2014  absurdworlds

   License LGPLv3-only:
   GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
   This is free software: you are free to change and redistribute it.
   There is NO WARRANTY, to the extent permitted by law.
 */
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
