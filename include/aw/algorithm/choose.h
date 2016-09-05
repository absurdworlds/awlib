/*
 * Copyright (C) 2016  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_algorithm_choose_h
#define aw_algorithm_choose_h
namespace aw {
/*!
 * Choose one of three values, based on relation between a and b:
 * \return
 *    - first  value if (b < a)
 *    - second value if (a == b)
 *    - third  value if (a < b)
 */
template<typename T, typename R>
R choose(T a, T b, R a_greater, R equal, R b_greater)
{
	if (a < b) return b_greater;
	if (b < a) return a_greater;
	return equal;
}
} // namespace aw
#endif//aw_algorithm_choose_h
