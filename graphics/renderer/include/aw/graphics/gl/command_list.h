/*
 * Copyright (C) 2017-2024 hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_graphics_gl3_command_list_h
#define aw_graphics_gl3_command_list_h
#include <aw/types/strip.h>
#include <aw/types/containers/any_buffer.h>

#include <functional>
#include <vector>
namespace aw::gl3 {
struct render_context;


/*
 * Store any command object that is not larger that `max_size`.
 * Temporary, until I get a generic any_storage class
 */
struct command_storage {
	static constexpr size_t max_size = 32;
	using storage_type = any_buffer<max_size>;
	using invoke_func  = void(storage_type&, render_context& ctx);

	template<typename T>
	command_storage(T&& t)
	{
		assign(std::forward<T>(t));
	}

	template<typename T>
	void assign( T&& t )
	{
		static_assert(std::is_trivially_destructible_v<T>);
		storage.emplace<std::remove_cvref_t<T>>(std::forward<T>(t));
		invoke  = +[] (storage_type& data, render_context& ctx)
		{
			std::invoke(data.get<T&>(), ctx);
		};
	}

	void operator()( render_context& ctx )
	{
		invoke(storage, ctx);
	}

	invoke_func* invoke;
	storage_type storage;
};


struct command_list {
	std::vector< command_storage > cmds;

	template<typename T>
	void add( T&& cmd )
	{
		cmds.emplace_back( std::forward<T>(cmd) );
	}

	void render(render_context& ctx)
	{
		for (auto& cmd : cmds)
			cmd(ctx);
	}
};
} // namespace aw::gl3
#endif//aw_graphics_gl3_command_list_h
