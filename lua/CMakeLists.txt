find_package(Lua REQUIRED)


aw_add_library(awlua SHARED
	GLOB_HEADERS
	SOURCES
		metatable_utils.c++
	EXPORT_NAME
		lua
)

target_include_directories(awlua
	INTERFACE
		${LUA_INCLUDE_DIR})

target_link_libraries(awlua
	INTERFACE
		awtypes
		${LUA_LIBRARIES})

target_compile_definitions(awlua PRIVATE AW_MODULE_LUA)
