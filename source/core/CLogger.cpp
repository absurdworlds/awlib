#include "CLogger.h"

namespace hrengin
{

ILogger* createLogger()
{
	return new CLogger();
}

CLogger::CLogger()
{
}

CLogger::~CLogger()
{
}

void CLogger::push(std::string msg)
{
	// woohoo, iterators incompatible
	//for(std::vector<ILogBook*>::iterator it; it != logs_.end(); ++it) {
	for(auto it = logs_.begin(); it != logs_.end(); ++it) {
		(*it)->log(msg);
	}
}

void CLogger::addLog(ILogBook* log)
{
	logs_.push_back(log);
}
} // namespace hrengin
