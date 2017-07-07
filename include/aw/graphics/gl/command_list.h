/*
 * Copyright (C) 2017  hedede <haddayn@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_graphics_gl3_command_list_h
#define aw_graphics_gl3_command_list_h
#include <vector>
#include <utility>
namespace aw {
namespace gl3 {
struct render_context;


/*
 * Store any command object that is not larger that `max_size`.
 * Temporary, until I get a generic any_storage class
 */
struct command_storage {
	static constexpr size_t max_size = 32;
	using storage_type = std::aligned_storage<max_size, alignof(void*)>::type;
	using invoke_func  = void(void*, render_context& ctx);
	using generic_func  = void(void*);

	template<typename T>
	command_storage(T&& t)
	{
		insert(std::forward<T>(t));
	}

	template<typename T>
	void assign( T&& t )
	{
		destroy(&data);
		insert(std::forward<T>(t));
	}

	template<typename T>
	void insert( T&& t )
	{
		static_assert( alignof(T) <= alignof(void*) );
		static_assert( sizeof(T)  <= max_size );
		using cmd_type = remove_reference<T>;
		new (&data) cmd_type{ std::forward<T>(t) };
		invoke  = +[] (void* data, render_context& ctx)
		{
			static_cast<cmd_type*>(data)->operator()(ctx);
		};
		destroy = +[] (void* data)
		{
			static_cast<cmd_type*>(data)->~cmd_type();
		};
	}

	void operator()( render_context& ctx )
	{
		invoke(&data, ctx);
	}

	invoke_func*  invoke;
	generic_func* destroy;
	storage_type  data;
};




struct command_list {
	std::vector< command_storage > cmds;

	void render(render_context& ctx)
	{
		for (auto& cmd : cmds)
			cmd(ctx);
	}
};
} // namespace gl3
} // namespace aw
#endif//aw_graphics_gl3_command_list_h
