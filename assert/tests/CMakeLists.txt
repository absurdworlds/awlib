
set(SOURCES
	assert.c++)

add_executable(test_assert ${SOURCES})
target_link_libraries(test_assert
	PRIVATE
		awutils
		awtest
		awassert)
