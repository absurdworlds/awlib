aw_add_library(awtest INTERFACE
	HEADERS
		include/aw/test/registry.h
		include/aw/test/report.h
		include/aw/test/report_impl.h
		include/aw/test/print.h
		include/aw/test/segv_handler.h
		include/aw/test/test_case.h
		include/aw/test/test.h
		include/aw/test/main.h
	EXPORT_NAME
		test
)

target_link_libraries(awtest
	INTERFACE
		awutils
		awplatform)

add_subdirectory(test_runner)
