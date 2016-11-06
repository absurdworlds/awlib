/*
 * Copyright (C) 2016  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_internal_gl3_program_h
#define aw_internal_gl3_program_h
#include <aw/graphics/gl/program.h>
namespace aw {
namespace gl3 {
/* Kinda hackish thing to keep external code from
 * manipulating shader handles, without adding bunch of friends */

struct program;
struct program_handle {
	GLuint handle;
	operator GLuint() { return handle; }
};

program::operator program_handle()
{
	return {_program};
}

namespace {
GLuint handle(program& prg) { return program_handle(prg); }
}


} // namespace gl3
} // namespace aw
#endif//aw_internal_gl3_handles_h
