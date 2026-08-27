aw_add_test(test_string
	SOURCES
		case.c++
		compose.c++
		to_string.c++
		split.c++
		split_iterator.c++
		lazy_split.c++
		join.c++
		misc.c++
		parse.c++
		repeat.c++
		strto.c++
		parser_helpers.c++
		conv_integer.c++
		to_string_composite_int.c++)

target_link_libraries(test_string
	PRIVATE
		awstring
		awmath # to_string.c++ prints vectors and matrices
		awplatform
		awtest
		awtest_main)
