
set(SOURCES
	assert.c++
	cassert_included_after.c++
	cassert_included_before.c++)

add_executable(test_assert ${SOURCES})
target_link_libraries(test_assert
	PRIVATE
		awutils
		awtest
		awtest_main
		awassert)
