
set(SOURCES
    to_string.cpp split.cpp split_iterator.cpp lazy_split.cpp
    join.cpp compose.cpp misc.cpp repeat.c++)

add_executable(test_string ${SOURCES})
target_link_libraries(test_string
	PRIVATE
		awstring
		awplatform
		awtest
		awtest_main)
