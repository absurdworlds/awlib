/*
 * Copyright (C) 2016 Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_thread_worker_h
#define aw_thread_worker_h
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
namespace aw {
namespace thread {
/*!
 * Simple worker thread, which continues running until destroyed or
 * manually killed.
 * Executes signle task and waits until next one.
 */
struct worker {
	typedef std::function<void()> Task;

	worker();
	~worker();

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
} // namespace thread
} // namespace aw
#endif//aw_thread_worker_h
