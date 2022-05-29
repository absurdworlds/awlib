/*
 * Copyright (C) 2016  absurdworlds
 * Copyright (C) 2016  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_reinterpret_type
#define aw_reinterpret_type
#include <cstring>
#include <algorithm>
#include <aw/types/strip.h>
#include <aw/types/traits/basic_traits.h>
namespace aw {
/*!
 * Copy raw sequence of bytes into an object of type T.
 */
template<typename T>
T& copy_from_memory(T&& out, void const* memory)
{
	static_assert(is_trivially_copyable<remove_reference<T>>,
	              "Output type must be trivially copyable!");
	std::memcpy(&out, memory, sizeof(T));
	return out;
}
/*!
 * Copy object of type T as raw sequence of bytes.
 */
template<typename T>
void* copy_to_memory(T const& in, void* memory)
{
	static_assert(is_trivially_copyable<T>,
	              "Input type must be trivially copyable!");
	std::memcpy(memory, in, sizeof(T));
	return memory;
}

/*!
 * Reinterpret value of type Input as a value of type Output.
 *
 * For example
 *     int x = reinterpret<int>(1.0f);
 * will reinterpret float `1.0f` into integer.
 *
 * \note
 *     Sizes of both types must match.
 * \note
 *     Usually compilers optimize it to few mov instructions.
 */
template<typename Output, typename Input>
Output reinterpret(Input&& in)
{
	static_assert(is_trivially_copyable<remove_reference<Input>>,
	              "Input type must be trivially copyable");
	static_assert(is_trivially_copyable<Output>,
	              "Output type must be trivially copyable");
	static_assert(sizeof(Output) == sizeof(Input),
	              "cannot reinterpret type: sizes don't match");
	Output out;
	std::memcpy(&out, &in, sizeof(Input));
	return out;
}

/*!
 * Same as reinterpret(), but allows to interpret structs of inequal sizes.
 * It will truncate input if the Output type is smaller
 * 
 * \note
 *     Usually compilers optimize it to few mov instructions.
 */
template<typename Output, typename Input>
Output reinterpret_any(Input&& in)
{
	static_assert(is_trivially_copyable<remove_reference<Input>>,
	              "Input type must be trivially copyable");
	static_assert(is_trivially_copyable<Output>,
	              "Output type must be trivially copyable");
	constexpr size_t size = std::min(sizeof(Output), sizeof(Input));
	Output out{};
	std::memcpy(&out, &in, size);
	return out;
}

/*!
 * Reinterpret raw memory as a value of type Output.
 */
template<typename Output>
Output reinterpret_memory(void const* in)
{
	Output out;
	copy_from_memory(&out, in);
	return out;
}
} // namespace aw
#endif//aw_reinterpret_type
