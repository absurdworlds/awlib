aw_add_test(test_functional
	SOURCES
		functional.c++)

target_link_libraries(test_functional
	PRIVATE
		awbase
		awtest
		awtest_main)
