aw_add_test(test_types
	SOURCES
		any_buffer.c++
    traits_promote.c++ traits_is_iterable.c++
    variant.c++ queue.c++ flat_map.c++
    circular_buffer.c++
    string_view.c++ array_view.c++
    tmpflag.c++)

target_link_libraries(test_types
	PRIVATE
		awtypes
		awtest
		awtest_main)
