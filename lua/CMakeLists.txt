find_package(Lua REQUIRED)


aw_add_library(awlua INTERFACE
	GLOB_HEADERS
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
