/*
 * Copyright (C) 2016  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_graphics_gl3_program_manager_h
#define aw_graphics_gl3_program_manager_h
#include <vector>
#include <aw/graphics/gl/program.h>
//#include <aw/types/containers/flat_map.h>
#include <aw/types/string_view.h>
namespace aw {
namespace gl3 {
struct program_uniform_locations {
	uniform_location model_to_camera;
};

struct program_aux {
	program_uniform_locations loc;
};

//TODO: this is placeholder, until I think of something better
struct program_ref {
	program_ref(program& prg, program_aux& aux)
		: prg{&prg}, aux{&aux}
	{}

	program_ref& operator=(program_ref const& other)
	{
		prg = other.prg;
		aux = other.aux;
		return *this;
	}

	program& operator*() { return *prg; }

	program* get()        { return prg; }
	program* operator->() { return prg; }

	uniform_proxy operator[]( const char* name ) { return (*prg)[name]; }

	program_uniform_locations& uniform_locations()
	{
		return aux->loc;
	}

	explicit operator program_handle()
	{
		return program_handle{*prg};
	}

private:
	program*     prg;
	program_aux* aux;
};

struct program_manager {
	using ref = program_ref;
	ref operator[]( size_t idx )
	{
		return { programs[idx], aux[idx] };
	}

	// TODO: create from shader list, not this
	size_t create_program( string_view vsh, string_view fsh );

	// TODO: array_chain with freelist
	std::vector<program> programs;
	std::vector<program_aux> aux;
};

} // namespace gl3
} // namespace aw
#endif//aw_graphics_gl3_program_manager_h
