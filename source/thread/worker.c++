/*
 * Copyright (C) 2016 Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#include <cassert>
#include <aw/thread/worker.h>
namespace aw {
namespace thread {
worker::worker()
{
	thread = std::thread(&worker::loop, this);
}

worker::~worker()
{
	if (!done)
		kill();
}

bool worker::busy() const
{
	return static_cast<bool>(task);
}

void worker::start(Task task)
{
	assert(!done);

	{
		std::lock_guard lock{mutex};
		this->task = task;
	}
	cond.notify_one();
}

void worker::wait()
{
	assert(!done);

	std::unique_lock lock{mutex};
	cond.wait(lock, [this] {return !task;});
}

void worker::kill()
{
	assert(!done && "Attempted to kill thread twice.");

	{
		std::lock_guard lock{mutex};
		done = true;
	}
	cond.notify_one();

	thread.join();
}

void worker::loop()
{
	assert(!done);

	while (true) {
		std::unique_lock lock{mutex};
		cond.wait(lock, [this] {return done || task;});

		if (done)
			return;

		task();
		task = nullptr;

		lock.unlock();
		cond.notify_one();
	}
}
} // namespace thread
} // namespace aw
