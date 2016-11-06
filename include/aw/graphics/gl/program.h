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
#include <vector>
namespace aw {
namespace gl3 {
struct program {
	program();
	~program() { cleanup(); }

	program(program const&) = delete;
	program(program&& other)
		: _program{other._program}
	{
		other._program = 0;
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
	// TODO: array_view
	bool link(std::vector<shader>& shaders);

	struct uniform_value uniform(char const* name);

private:
	friend struct program_handle handle(program&);

	void cleanup();
	GLuint _program;
};

} // namespace gl3
} // namespace aw
#endif//aw_graphics_gl3_program_h
