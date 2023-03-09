
add_executable(test_lua main.c++)

target_link_libraries(test_lua
	PRIVATE
		awlua
		awutils)
