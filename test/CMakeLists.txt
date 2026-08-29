aw_add_library(awtest INTERFACE
	HEADERS
		include/aw/test/registry.h
		include/aw/test/report.h
		include/aw/test/report_impl.h
		include/aw/test/print.h
		include/aw/test/segv_handler.h
		include/aw/test/helpers/lifetime_tracker.h
		include/aw/test/helpers/copy_move_tracker.h
		include/aw/test/test_case.h
		include/aw/test/test_context.h
		include/aw/test/test.h
		include/aw/test/main.h
	EXPORT_NAME
		test
)

target_link_libraries(awtest
	INTERFACE
		awutils
		awplatform)

# so that the reports can name source files relative to the source tree
target_compile_definitions(awtest
	INTERFACE
		AW_TEST_SOURCE_ROOT="${CMAKE_SOURCE_DIR}/")

add_subdirectory(test_runner)
