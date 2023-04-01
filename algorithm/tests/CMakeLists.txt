aw_add_test(test_algo
	SOURCES
		split.c++ join.c++
		exchange.c++
		common_prefix.c++)

target_link_libraries(test_algo
	PRIVATE
		awalgo
		awtest
		awtest_main)
