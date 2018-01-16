/*
 * Copyright (C) 2016 Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_thread_spin_lock_h
#define aw_thread_spin_lock_h
#include <thread>
#include <atomic>
namespace aw {
namespace thread {
/*!
 * Simple spin_lock implementation.
 * (Based on cppreference.com atomic_flag example)
 */
struct spin_lock {
	spin_lock() = default;
	spin_lock(spin_lock const&) = delete;
	spin_lock& operator=(spin_lock const&) = delete;
	~spin_lock() = default;

	void lock()
	{
		while (flag.test_and_set(std::memory_order_acquire));
	}

	void unlock()
	{
		flag.clear(std::memory_order_release);
	}

private:
	std::atomic_flag flag = ATOMIC_FLAG_INIT;
};
} // namespace thread
} // namespace aw
#endif//aw_thread_spin_lock_h
