aw_add_test(test_ranges
	SOURCES
		slice.c++
		value_range.c++
		paired.c++
		ipairs.c++
		zip.c++
		reverse.c++)

target_link_libraries(test_ranges
	PRIVATE
		awbase
		awstring # zip prints pairs with aw/string/to_string
		awtest
		awtest_main)
