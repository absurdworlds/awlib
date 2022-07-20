aw_add_library(awtest_main STATIC
	SOURCES
		main.c++
	EXPORT_NAME
		test-runner
)

target_link_libraries(awtest_main
	PUBLIC awtest)
