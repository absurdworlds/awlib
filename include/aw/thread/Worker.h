/*
 * Copyright (C) 2016 Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_thread_Worker
#define aw_thread_Worker
#include <thread>
#include <mutex>
#include <condition_variable>
namespace aw {
class Worker {
public:
	typedef std::function<void()> Task;

	Worker();
	~Worker();

	/*!
	 * Runs the task in this worker thread
	 */
	void start(Task task);
	
	/*!
	 * Blocks current thread until the worker thread finishes
	 */
	void wait();

	/*!
	 * Kills worker thread.
	 * No tasks can be run after thread is killed.
	 */
	void kill();

	/*!
	 * Returns true if tread has task
	 */
	bool busy() const;

private:
	void loop();

	std::mutex mutex;
	std::condition_variable cond;

	bool done = false;
	Task task = nullptr;

	std::thread thread;
};
} // namespace aw
#endif//aw_thread_Worker
