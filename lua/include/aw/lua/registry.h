/*
 * Copyright (C) 2023 absurdworlds
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */
#ifndef aw_lua_registry_h
#define aw_lua_registry_h

#include <aw/lua/class_def.h>

#include <typeindex>
#include <unordered_map>

namespace aw::lua {

class registry {
	std::unordered_map<std::type_index, class_def*> class_defs;

	void push_reference(lua_State* L, const std::type_info& ti, void* instance)
	{
		auto it = class_defs.find(ti);
		if (it == class_defs.end()) {
			assert(!"Class is not registered");
			lua_pushnil(L);
			return;
		}

		auto& def = it->second;
		def->push_reference(L, instance);
	}

	void bind(lua_State* L)
	{
		lua_pushlightuserdata(L, this);
		lua_setfield(L, LUA_REGISTRYINDEX, "aw::registry");
	}

	// TODO: support for multiple lua_States?
	lua_State* L;

public:
	registry() = default;
	explicit registry(lua_State* L)
		: L(L)
	{
		bind(L);
	}
	template<typename T, typename Properties = properties<>, typename Methods = methods<>>
	void register_class(Properties p = Properties{}, Methods m = Methods{})
	{
		class_defs[typeid(T)] = new class_def_impl<T, Properties, Methods>();
	}

	template<typename T>
	void push_reference(T* instance)
	{
		push_reference(L, typeid(T), instance);
	}

	template<typename T>
	void push_reference(lua_State* L, T* instance)
	{
		push_reference(L, typeid(T), instance);
	}
};

template<typename T>
void push_reference(lua_State* L, T& member)
{
	lua_pushstring(L, "aw::registry");
	lua_gettable(L, LUA_REGISTRYINDEX);
	auto ptr = lua_touserdata(L, -1);
	if (!ptr) {
		assert(!"aw::registry is not bound to this context!");
		lua_pushnil(L);
		return;
	}

	auto* reg = static_cast<registry*>(ptr);

	reg->push_reference(L, &member);
}

} // namespace aw::lua

#endif // aw_lua_registry_h
