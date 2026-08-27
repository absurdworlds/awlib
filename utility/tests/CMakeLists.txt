aw_add_test(test_utility
	SOURCES
	static_object.c++
	memory_pool.c++
	utf8toutf16.c++
	MurmurHash3.c++
	hash_combine.c++
	type_name.c++
)

target_link_libraries(test_utility
	PRIVATE
		awutils
		awplatform
		awtest
		awtest_main)
