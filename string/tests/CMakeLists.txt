aw_add_test(test_string
	SOURCES
		case.c++
		compose.cpp
		to_string.cpp
		split.cpp
		split_iterator.cpp
		lazy_split.cpp
		join.cpp
		misc.cpp
		repeat.c++)

target_link_libraries(test_string
	PRIVATE
		awstring
		awplatform
		awtest
		awtest_main)
