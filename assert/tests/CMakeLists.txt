aw_add_test(test_assert
	SOURCES
		assert.c++
		cassert_included_after.c++
		cassert_included_before.c++)

target_link_libraries(test_assert
	PRIVATE
		awutils
		awtest
		awtest_main
		awassert)
