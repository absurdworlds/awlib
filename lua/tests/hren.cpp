#include <memory>
#include <stdio.h>
#include <stdlib.h>
#include <string>
extern "C" {
#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>
}
namespace {
void PushSimpleValue(lua_State *lua, int value) {
	// Creating userdata value which will be shared between C++ and Lua.
	// This userdata is a pointer which point to memory allocated by Lua.
	auto &udata = *(int *)lua_newuserdata(lua, sizeof(int));
	// This is a simple value. Lua just allocates the memory to it, but we need to
	// initialize it with some value.
	udata = value;
	// creating the metatable for the userdata by which the userdata can be access
	// or call in the Lua such as function and return the stored value of the
	// userdata.
	lua_newtable(lua);
	lua_pushstring(lua, "__call");
	lua_pushcfunction(lua, [](lua_State *lua) {
		auto &udata = *(int *)lua_touserdata(lua, 1);
		lua_pushinteger(lua, udata);
		return 1;
	});
	lua_settable(lua, -3);
	lua_setmetatable(lua, -2);
}
struct Struct {
	int x = 0;
	int y = 0;
};
void PushSimpleStruct(lua_State *lua, const Struct &s) {
	// Simple Struct userdata value which will be shared between C++ and Lua.
	auto &udata = *(Struct *)lua_newuserdata(lua, sizeof(Struct));
	// Lua just allocates the memory to it, but we need to initialize it.
	udata = s;
	// creating the metatable for the userdata by which the userdata can be access
	// or call in the Lua such as function and return the stored value of the
	// userdata.
	lua_newtable(lua);
	lua_pushstring(lua, "__index");
	lua_pushcfunction(lua, [](lua_State *lua) {
		auto &udata = *(Struct *)lua_touserdata(lua, 1);
		const std::string key = lua_tostring(lua, 2);
		if (key == "x") {
			lua_pushinteger(lua, udata.x);
		} else if (key == "y") {
			lua_pushinteger(lua, udata.y);
		} else {
			lua_pushnil(lua);
		}
		return 1;
	});
	lua_settable(lua, -3);
	lua_setmetatable(lua, -2);
}
struct TObject {
	int v;
	std::string s;
};
void OwnedObjectPush(lua_State *lua, TObject &&t) {
	// TObject userdata value which will be shared between C++ and Lua.
	auto udata = (TObject *)lua_newuserdata(lua, sizeof(TObject));
	new (udata) TObject(std::move(t));
	// Create a metatable for the userdata through that object can be access in 2
	// ways- "__gc" and "__index"
	lua_newtable(lua);
	lua_pushstring(lua, "__gc");
	lua_pushcfunction(lua, [](lua_State *lua) {
		(void)printf("Releasing shared object.\n");
		auto udata = (TObject *)lua_touserdata(lua, 1);
		udata->~TObject();
		return 0;
	});
	lua_settable(lua, -3);
	lua_pushstring(lua, "__index");
	lua_pushcfunction(lua, [](lua_State *lua) {
		auto &udata = *(TObject *)lua_touserdata(lua, 1);
		const std::string key = lua_tostring(lua, 2);
		if (key == "v") {
			lua_pushinteger(lua, udata.v);
		} else if (key == "s") {
			lua_pushlstring(lua, udata.s.c_str(), udata.s.length());
		} else {
			lua_pushnil(lua);
		}
		return 1;
	});
	lua_settable(lua, -3);
	lua_setmetatable(lua, -2);
}
void PushShared(lua_State *lua, const std::shared_ptr<TObject> &t) {
	// Create TObject userdata value
	//
	// The "std::shared_ptr" allows the shared object to own its own reference in
	// Lua .
	auto urdata = (std::shared_ptr<TObject> *)lua_newuserdata(
			lua, sizeof(std::shared_ptr<TObject>));
	// allocate the memory and initialize it.
	new (urdata) std::shared_ptr<TObject>(t);
	lua_newtable(lua);
	lua_pushstring(lua, "__gc");
	lua_pushcfunction(lua, [](lua_State *lua) {
		(void)printf("Shared object releasing.\n");
		auto urdata = (std::shared_ptr<TObject> *)lua_touserdata(lua, 1);
		urdata->~shared_ptr<TObject>();
		return 0;
	});
	lua_settable(lua, -3);
	lua_pushstring(lua, "__index");
	lua_pushcfunction(lua, [](lua_State *lua) {
		auto &urdata = **(std::shared_ptr<TObject> *)lua_touserdata(lua, 1);
		const std::string key = lua_tostring(lua, 2);
		if (key == "v") {
			lua_pushinteger(lua, urdata.v);
		} else if (key == "s") {
			lua_pushlstring(lua, urdata.s.c_str(), urdata.s.length());
		} else {
			lua_pushnil(lua);
		}
		return 1;
	});
	lua_settable(lua, -3);
	lua_setmetatable(lua, -2);
}
// load the "chunck" (the bloack of code of the lua script), insert and execute.
void WithLua(lua_State *lua, const char *chunk, int nargs) {
	(void)luaL_loadstring(lua, chunk);
	lua_insert(lua, -nargs - 1);
	(void)lua_call(lua, nargs, 0);
}
} // namespace
int main() {
	// Lua instance creating ..
	const auto lua = luaL_newstate();
	// Lua libraries load
	lua_gc(lua, LUA_GCSTOP, 0); // Temporarily disable the garbage collector
	luaL_openlibs(lua);
	// enable the garbage collector
	lua_gc(lua, LUA_GCRESTART, 0);
	// calling to the function with as a Lua userdata and give it to a Lua script
	// to use.
	PushSimpleValue(lua, 100);
	WithLua(lua, R"lua(
local urdata = ...
print("Simple value: " .. urdata())
)lua",
					1);
	// object sharing to Lua by the userdata
	TObject Tbobj1;
	Tbobj1.v = 99;
	Tbobj1.s = "Hello,";
	OwnedObjectPush(lua, std::move(Tbobj1));
	WithLua(lua, R"lua(
local urdata = ...
print("An owned object: (v:" .. urdata.v .. ", s:'" .. urdata.s .. "')")
)lua",
					1);
	Struct st;
	st.x = 20;
	st.y = 60;
	PushSimpleStruct(lua, st);
	WithLua(lua, R"lua(
local urdata = ...
print("THe Simple struct: (x:" .. urdata.x .. ", y:" .. urdata.y .. ")")
)lua",
					1);
	std::shared_ptr<TObject> Tbobj2{new TObject(), [&](TObject *p) {
																		delete p;
																		(void)printf(
																				"The shared object was destroyed!\n");
																	}};
	Tbobj2->v = 50;
	Tbobj2->s = "Hello!";
	PushShared(lua, Tbobj2);
	Tbobj2->v = 20;
	Tbobj2->s = "World.";
	Tbobj2.reset();
	WithLua(lua, R"lua(
local urdata = ...
print("The Shared object: (v:" .. urdata.v .. ", s:'" .. urdata.s .. "')")
)lua",
					1);
	// Lua instance destroy.
	(void)printf("Destroy Lua instance.\n");
	lua_close(lua);
	(void)printf("Done.\n");
	// finished
	return EXIT_SUCCESS;
}
