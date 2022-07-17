aw_add_test(test_log
	SOURCES
		log_filter.c++
		log_tester.h)

target_link_libraries(test_log
	PRIVATE
		awlog
		awplatform
		awtest
		awtest_main
)
