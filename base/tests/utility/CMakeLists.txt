aw_add_test(test_base_utility
	SOURCES
		byteswap.c++
		on_scope_exit.c++)

target_link_libraries(test_base_utility
	PRIVATE
		awbase
		awtest
		awtest_main)
