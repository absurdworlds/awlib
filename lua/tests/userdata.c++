/*
 * Copyright (C) 2026  Hedede <hededrk@gmail.com>
 *
 * License LGPLv3 or later:
 * GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
 * This is free software: you are free to change and redistribute it.
 * There is NO WARRANTY, to the extent permitted by law.
 */

#include <aw/lua/registry.h>

#include <aw/test/test.h>

#include <string>

TestFile( "aw::lua bindings" );

namespace aw::lua {
namespace {
struct point {
	int x = 1;
	int y = 2;

	void touch() { touched = true; }

	// not exposed to Lua: records whether the method ran on this object
	bool touched = false;
};

//! A second bound class for verifying userdata type safety
struct other {
	long long filler[8] = {};
};

struct fixture {
	lua_State* L = luaL_newstate();
	registry reg{L};

	point p;
	other o;

	fixture()
	{
		luaL_openlibs(L);

		reg.register_class<point,
			properties<
				property<"x", &point::x>,
				property<"y", &point::y>
			>,
			methods<
				method<"touch", &point::touch>
			>>();

		reg.register_class<other, properties<>, methods<>>();

		reg.push_reference(L, &p);
		lua_setglobal(L, "p");

		reg.push_reference(L, &o);
		lua_setglobal(L, "o");
	}

	~fixture()
	{
		lua_close(L);
	}

	//! Run \a script, returning the error message, or "" if it succeeded
	std::string run(char const* script)
	{
		if (luaL_dostring(L, script) == LUA_OK)
			return {};

		std::string msg = lua_tostring(L, -1);
		lua_pop(L, 1);
		return msg;
	}
};

bool mentions(std::string const& msg, std::string_view what)
{
	return msg.find(what) != std::string::npos;
}
} // namespace

Test(lua_bound_method_runs_on_its_own_class) {
	fixture f;

	Checks {
		TestEqual( f.run("p:touch()"), std::string() );
		TestAssert( f.p.touched );
	}
}

Test(lua_property_reads_its_own_class) {
	fixture f;

	Checks {
		TestEqual( f.run("assert(p.x == 1 and p.y == 2)"), std::string() );
	}
}

Test(lua_method_rejects_other_userdata) {
	fixture f;

	auto msg = f.run("local m = getmetatable(p).touch; m(o)");

	Checks {
		TestAssert( !msg.empty() );
		TestAssert( mentions(msg, "point") );
		TestAssert( !f.p.touched );
	}
}

Test(lua_method_rejects_non_userdata) {
	fixture f;

	Checks {
		for (auto* arg : {"42", "nil", "\"str\"", "{}", "print"}) {
			auto script = std::string("local m = getmetatable(p).touch; m(") + arg + ")";
			TestAssert( !f.run(script.c_str()).empty() );
		}
		TestAssert( !f.p.touched );
	}
}

Test(lua_index_rejects_other_userdata) {
	fixture f;

	Checks {
		TestAssert( !f.run("local i = getmetatable(p).__index; i(o, \"x\")").empty() );
		TestAssert( !f.run("local i = getmetatable(p).__index; i(42, \"x\")").empty() );
	}
}
} // namespace aw::lua
