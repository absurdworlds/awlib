aw_add_test(test_bit
	SOURCES
		mask.c++
		manip.c++
		count.c++)

target_link_libraries(test_bit
	PRIVATE
		awbase
		awtest
		awtest_main)
