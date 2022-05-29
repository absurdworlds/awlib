/*
 * Copyright (C) 2016-2022  absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_types_byte_buffer_h
#define aw_types_byte_buffer_h
#include <memory>
namespace aw {
/**
 * Convenience wrapper for temporary malloc()ed data.
 */
template<typename byte_type>
struct basic_buffer {
	struct free_deleter {
		void operator()(byte_type* memory) { std::free(memory); }
	};

	unsigned char* data() { return memory.get(); }

	size_t size = 1024;
	std::unique_ptr<byte_type, free_deleter> memory{ static_cast<byte_type*>(std::malloc(size)) };
};

using byte_buffer = basic_buffer<std::byte>;
using char_buffer = basic_buffer<char>;

} // namespace aw
#endif//aw_types_byte_buffer_h
