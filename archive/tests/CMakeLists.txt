aw_add_test(test_archive
	SOURCES
		archive.c++
)

target_link_libraries(test_archive
	PRIVATE
		awarchive
		awtest
		awtest_main
)
