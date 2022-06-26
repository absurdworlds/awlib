
set(HEADERS
	include/aw/test/registry.h
	include/aw/test/report.h
	include/aw/test/report_impl.h
	include/aw/test/print.h
	include/aw/test/test_case.h
	include/aw/test/test.h
	include/aw/test/main.h)

add_library(awtest INTERFACE ${HEADERS})
target_include_directories(awplatform PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(awtest
    INTERFACE
        awutils
        awplatform)

add_subdirectory(test_runner)
