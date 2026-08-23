aw_add_test(test_iterators
	SOURCES
		wrapper.c++)

target_link_libraries(test_iterators
	PRIVATE
		awbase
		awtest
		awtest_main)
