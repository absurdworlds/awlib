aw_add_test(test_algo
	SOURCES
		astar.c++
		common_prefix.c++
		exchange.c++
		join.c++
		shift.c++
		split.c++)

target_link_libraries(test_algo
	PRIVATE
		awalgo
		awmath
		awtest
		awtest_main)
