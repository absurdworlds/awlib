/*
 * Copyright (C) 2016  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_utility_random_mersenne_twister_h
#define aw_utility_random_mersenne_twister_h
#include <random>
#include <functional>
namespace aw {
/*!
 * Create mersenne_twister_engine,
 * properly seeded from std::random_device
 */
template<typename Engine = std::mt19937>
Engine create_mersenne_twister_engine()
{
	using result_type = typename Engine::result_type;
	result_type data[Engine::state_size];

	std::random_device rd;
	std::generate(std::begin(data), std::end(data), std::ref(rd));
	std::seed_seq seeds(std::begin(data), std::end(data));

	return Engine{seeds};
}
} // namespace aw
#endif//aw_utility_random_mersenne_twister_h
