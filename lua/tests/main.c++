#include <aw/lua/registry.h>

namespace aw::lua {

#if 0
// TODO: rewrite without printfs and move to debug.h
static void dump_stack (lua_State *L)
{
	int top=lua_gettop(L);
	for (int i=1; i <= top; i++) {
		printf("%d\t%s\t", i, luaL_typename(L,i));
		switch (lua_type(L, i)) {
		case LUA_TNUMBER:
			printf("%g\n",lua_tonumber(L,i));
			break;
		case LUA_TSTRING:
			printf("%s\n",lua_tostring(L,i));
			break;
		case LUA_TBOOLEAN:
			printf("%s\n", (lua_toboolean(L, i) ? "true" : "false"));
			break;
		case LUA_TNIL:
			printf("%s\n", "nil");
			break;
		default:
			printf("%p\n",lua_topointer(L,i));
			break;
		}
	}
}
#endif
} // namespace aw::lua

#include <iostream>

int main()
{
	lua_State* L = luaL_newstate();

	luaL_openlibs(L);

	struct vec4 {
		int x;
		int y;
		int z;
		int w;

		void print() const
		{
			std::cout << "x"<< x << ','
			          << "y"<< y << ','
				  << "z"<< z << ','
			          << "w"<< w <<'\n';
			}
	};


	struct mat4 {
		vec4 a;
		vec4 b;
		vec4 c;
		vec4 d;
	};

	mat4 hr {
		.a = { .x = 11, .y = 12, .z = 13, .w = 14 },
		.b = { .x = 21, .y = 22, .z = 23, .w = 24 },
		.c = { .x = 31, .y = 32, .z = 33, .w = 34 },
		.d = { .x = 41, .y = 42, .z = 43, .w = 44 },
	};

	using namespace aw::lua;

	registry reg(L);
	reg.register_class<vec4,
		properties<
			property<"x", &vec4::x>,
			property<"y", &vec4::y>,
			property<"z", &vec4::z>,
			property<"w", &vec4::w>
		>,
		methods<
			method<"print", &vec4::print>
		>>();

	reg.register_class<mat4,
		properties<
			property<"a", &mat4::a>,
			property<"b", &mat4::d>,
			property<"c", &mat4::c>,
			property<"d", &mat4::b>
		>>();

	reg.push_reference(L, &hr);
	lua_setglobal(L, "m");

	const int ec = luaL_dostring(L, R"(
	print(m.a.x)
	m.b:print()
	print(m.c.z)
	m.d:print()
	--local h = Hren:new()
)");

	if (ec != LUA_OK) {
		std::cout << lua_tostring(L, -1) << '\n';
		lua_pop(L, 1);
	}

	return 1;
}
