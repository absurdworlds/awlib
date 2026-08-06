aw_add_test(test_lua
	SOURCES
		userdata.c++)

target_link_libraries(test_lua
	PRIVATE
		awlua
		awutils
		awtest
		awtest_main)

add_executable(awlua-demo main.c++)

target_link_libraries(awlua-demo
	PRIVATE
		awlua
		awutils)
