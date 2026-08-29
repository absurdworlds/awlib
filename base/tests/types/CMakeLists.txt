aw_add_test(test_types
	SOURCES
		any_buffer.c++
		variant.c++
		variant_converter.c++
		variant_cast.c++
		enum.c++
		traits_decay.c++
    traits_promote.c++ traits_is_iterable.c++
    traits_is_container.c++
    queue.c++ flat_map.c++
    circular_buffer.c++
    array_chain.c++
    char_buffer.c++
    string_view.c++ array_view.c++
    tmpflag.c++
    reinterpret.c++
		compint.c++
		result.c++
)

target_link_libraries(test_types
	PRIVATE
		awtypes
		awmath # any_buffer.c++ stores matrices
		awtest
		awtest_main)
