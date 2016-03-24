/*
 * Copyright (C) 2016 Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <cassert>
#include <aw/thread/Worker.h>
namespace aw {
Worker::Worker()
{
	thread = std::thread(&Worker::loop, this);
}

Worker::~Worker()
{
	if (!done)
		kill();
}

bool Worker::busy() const
{
	return task;
}

void Worker::start(Task task)
{
	assert(!done);

	{
		std::lock_guard<std::mutex> lock(mutex);
		this->task = task;
	}
	cond.notify_one();
}

void Worker::wait()
{
	assert(!done);

	std::unique_lock<std::mutex> lock(mutex);
	cond.wait(lock, [this] {return !task;});
}

void Worker::kill()
{
	assert(!done && "Attempted to kill thread twice.");

	{
		std::lock_guard<std::mutex> lock(mutex);
		done = true;
	}
	cond.notify_one();

	thread.join();
}

void Worker::loop()
{
	assert(!done);

	while (true) {
		std::unique_lock<std::mutex> lock(mutex);
		cond.wait(lock, [this] {return done || task;});

		if (done)
			return;

		task();
		task = nullptr;

		lock.unlock();
		cond.notify_one();
	}
}
} // namespace aw
