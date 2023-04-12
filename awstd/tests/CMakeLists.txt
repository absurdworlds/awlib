aw_add_test(test_awstd
	SOURCES
		source_location.c++)

target_link_libraries(test_awstd
	PRIVATE
		awstd
		awtest
		awtest_main
)
