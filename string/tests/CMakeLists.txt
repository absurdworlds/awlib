aw_add_test(test_string SOURCES
    to_string.cpp split.cpp split_iterator.cpp lazy_split.cpp
    join.cpp compose.cpp misc.cpp repeat.c++)

target_link_libraries(test_string
	PRIVATE
		awstring
		awplatform
		awtest
		awtest_main)
