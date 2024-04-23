/*
 * Copyright (C) 2016  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_graphics_gl3_uniform_block_h
#define aw_graphics_gl3_uniform_block_h
#include <aw/gl/wrapper/shader_enum.h>
#include <aw/graphics/export.h>
#include <aw/types/traits/basic_traits.h>
#include <aw/meta/conditional.h>
namespace aw {
namespace gl3 {
struct program;
using gl::program_handle;
using gl::uniform_block_index;

struct AW_GRAPHICS_EXP uniform_buffer {
	uniform_buffer(GLuint index, size_t size);
	~uniform_buffer() { cleanup(); }

	uniform_buffer(uniform_buffer&& other)
		: index{other.index}, ubo{other.ubo}
	{
		other.index = 0;
		other.ubo   = 0;
	}

	uniform_buffer& operator=(uniform_buffer&& other)
	{
		cleanup();
		index = other.index;
		ubo   = other.ubo;
		other.index = 0;
		other.ubo   = 0;
		return *this;
	}

	//TODO
	void set_data(size_t offset, void const* data, size_t size);

	//TODO:query
	template<typename T, typename... Ts, typename = enable_if<!is_pointer<T>>>
	void set_data(size_t offset, T const& obj, Ts const&... objs)
	{
		static_assert(is_pod<T>);
		void const* data = &obj;
		size_t size = sizeof(obj);

		set_data(offset, data, size);

		if constexpr(sizeof...(Ts) > 0)
			set_data(offset + size, objs...);
	}

	void bind(program_handle, uniform_block_index);
	void bind(program& prg, uniform_block_index);

private:
	void cleanup();

	GLuint index;
	GLuint ubo;
};
} // namespace gl3
} // namespace aw
#endif//aw_graphics_gl3_uniform_h
