#include "CLogger.h"

namespace hrengin
{

HRENGIN_API ILogger& createLogger()
{
	return *(new CLogger());
}

CLogger::CLogger()
{

}

CLogger::~CLogger()
{
	stop();
}

void CLogger::init()
{
	thread_ = std::thread(&CLogger::log, this);
}

void CLogger::push(std::string msg)
{
	std::unique_lock<std::mutex> lock(mutex_);
	msgQueue_.push_back(msg);
}

void CLogger::stop()
{
	stopped_ = true;
	while (!finished_)
	{
		std::this_thread::sleep_for(std::chrono::milliseconds(0));
	}

	thread_.join();
}

void CLogger::log()
{
	while (!stopped_) {
		if (msgQueue_.empty()) {
			//std::this_thread::yield();
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
		} else {
			std::unique_lock<std::mutex> lock(mutex_);
			std::string msg = msgQueue_.front();
			write(msg);
			msgQueue_.pop_front();
		}
	}

	finished_ = true;
}

void CLogger::write(std::string msg)
{
	if (msg != "\n")
	{
		fprintf(stderr, "%s ", msg.c_str());
	} else {
		fprintf(stderr, "\n");
	}
}

} // namespace hrengin