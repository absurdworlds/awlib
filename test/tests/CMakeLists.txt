aw_add_test(test_test
	SOURCES
		always_fail.c++)

target_link_libraries(test_test
	PRIVATE
		awtest
		awtest_main)
