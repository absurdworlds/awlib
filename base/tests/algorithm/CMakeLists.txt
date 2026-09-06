aw_add_test(test_algo
	SOURCES
		common_prefix.c++
		exchange.c++
		insert_sorted.c++
		join.c++
		shift.c++
		split.c++
		sort/sort_tests.c++
		sort/insertion_sort.c++
)

target_link_libraries(test_algo
	PRIVATE
		awalgo
		awtest
		awtest_main)

target_include_directories(test_algo
	PRIVATE
		${CMAKE_CURRENT_SOURCE_DIR})
