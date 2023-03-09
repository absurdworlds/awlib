/*
 * Copyright (C) 2023 absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_lua_class_def_h
#define aw_lua_class_def_h

#include <aw/utility/type_name.h>

#include <aw/lua/metatable_utils.h>
#include <aw/lua/userdata_utils.h>
#include <aw/lua/class_members.h>

namespace aw::lua {

class class_def {
	friend class registry;

	virtual void push_reference(lua_State* L, void* instance ) const = 0;
};

template<typename T, typename Properties, typename Methods>
class class_def_impl : public class_def
{
	std::string name = std::string(type_name<T>::name());

	void push_reference(lua_State* L, void* instance) const override
	{
		create_reference(L, static_cast<T*>(instance));
	}

	static int index(lua_State* L)
	{
		static property_binding<T> get_property = Properties::template get_property<T>;

		void* ptr = lua_touserdata(L, 1);
		auto instance = *reinterpret_cast<T**>(ptr);

		const auto key = lua_tostringview(L, 2);
		auto type = luaL_getmetafield(L, -2, key.data());
		if (type != LUA_TNIL)
			return 1;

		get_property(L, instance, key);

		return 1;
	}

	void create_metatable(lua_State *L) const
	{
		if (aw::lua::get_metatable(L, name.c_str()))
			return;

		std::vector<luaL_Reg> funcs;
		funcs.push_back({"__index", index});

		Methods::register_methods(funcs);

		aw::lua::create_metatable(L, name.c_str(), funcs);
	}

public:
	void create_reference(lua_State* L, T* instance) const
	{
		create_userdata_pointer(L, instance);
		create_metatable(L);
		lua_setmetatable(L, -2);
	}
};

} // namespace aw::lua

#endif // aw_lua_class_def_h
