aw_add_test(test_algo
	SOURCES
		common_prefix.c++
		exchange.c++
		insert_sorted.c++
		join.c++
		shift.c++
		split.c++)

target_link_libraries(test_algo
	PRIVATE
		awalgo
		awtest
		awtest_main)
