/*
 * Copyright (C) 2023 absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_lua_class_members_h
#define aw_lua_class_members_h

#include <aw/types/traits/members.h>
#include <aw/types/string_literal.h>
#include <aw/types/string_view.h>

#include <aw/utility/functional/rank.h>

#include <aw/lua/push_value.h>

#include <lua.hpp>

#include <vector>

namespace aw::lua {


template<string_literal Name, auto Method>
class method {
public:
	using Member = decltype(Method);
	using Class = class_of_t<Member>;
	static void register_method(std::vector<luaL_Reg>& methods)
	{
		luaL_Reg reg{
			.name = static_cast<const char*>(Name.value),
			.func = [] (lua_State* L)
			{
				void* ptr = lua_touserdata(L, 1);
				auto instance = *reinterpret_cast<Class**>(ptr);
				(instance->*Method)();
				return 0;
			}
		};

		methods.push_back(reg);
	}
};

template<typename... Methods>
class methods
{
public:
	static void register_methods(std::vector<luaL_Reg>& methods)
	{
		( Methods::register_method(methods), ... );
	}

};

template<typename T>
void push_reference(lua_State* L, T& member);


template<typename T>
auto push_member(lua_State* L, T& member, rank_tag<1>)
	-> decltype(push_value(L, member))
{
	push_value(L, member);
}

template<typename T>
auto push_member(lua_State* L, T& member, rank_tag<0>)
{
	push_reference(L, member);
}

template<typename Class, typename Member>
void push_member(lua_State* L, Class* instance, Member member)
{
	push_member(L, instance->*member, rank_tag<1>());
}


template<string_literal Name, auto Property>
class property {
public:
	using Member = decltype(Property);
	using Class = class_of_t<Member>;
	static bool access(lua_State* L, Class* instance, std::string_view key)
	{
		if (key == Name)
		{
			push_member(L, instance, Property);
			return true;
		}
		return false;
	}
};


template<typename T>
using property_binding = void(*)(lua_State* L, T* instance, std::string_view key);

template<typename... Properties>
class properties
{
public:
	template<typename T>
	static void get_property(lua_State* L, T* instance, std::string_view key)
	{
		bool exists = ( Properties::access(L, instance, key) || ... );
		if (!exists)
			lua_pushnil(L);
	}

};

} // namespace aw::lua

#endif // aw_lua_class_members_h
