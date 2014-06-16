#include <thread>
#include <vector>

#include <hrengin/base/CLogger.h>

namespace hrengin
{
std::vector<std::string> msg_;
std::thread logger_;
bool logger_loop = true;
void logmsg()
{
	while (logger_loop)
	{
		if (msg_.empty())
		{
			std::this_thread::yield();
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
		}
		else
		{
			std::string msg = msg_.back();
			fprintf(stderr, "%s ", msg.c_str());
			msg_.pop_back();
		}
	}
}

void CLogger::init()
{
	logger_ = std::thread(logmsg);
}

void CLogger::exit()
{
	logger_loop = false;
	logger_.join();
}

void CLogger::log(std::string msg)
{
	msg_.push_back(msg);
}

} // namespace hrengin