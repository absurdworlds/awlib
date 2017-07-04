/*
 * Copyright (C) 2016  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_graphics_gl3_program_h
#define aw_graphics_gl3_program_h
#include <aw/graphics/gl/shader.h>
#include <aw/graphics/gl/uniform.h>
#include <aw/types/array_view.h>
namespace aw {
namespace gl3 {
using gl::program_handle;

struct program {
	program();
	~program() { cleanup(); }

	program(program const&) = delete;
	program(program&& other)
		: _program{other._program}
	{
		other._program = gl::no_program;
	}

	void swap(program& other)
	{
		std::swap(_program, other._program);
	}

	program& operator=(program&& other)
	{
		cleanup();
		swap(other);
	}

	bool is_linked() const;
	bool link( array_ref<shader> shaders);


	/*!
	 * Get uniform location
	 */
	uniform_location uniform( char const* name );

	/*!
	 * Creates proxy object for setting and
	 * retrieving value of an uniform.
	 *
	 * Behavior is undefined if this program is not currently active.
	 */
	uniform_proxy operator[](uniform_location loc)
	{
		return { loc };
	}
	uniform_proxy operator[]( char const* name )
	{
		return { uniform( name ) };
	}

	explicit operator program_handle();

private:
	void cleanup();
	program_handle _program = gl::no_program;
};

} // namespace gl3
} // namespace aw
#endif//aw_graphics_gl3_program_h
