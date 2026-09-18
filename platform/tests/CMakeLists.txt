
set(SOURCES
	os_version.c++
	native_file.c++
	mmap_file.c++
)

if(NOT EMSCRIPTEN)
	list(APPEND SOURCES process.c++)
endif()

aw_add_test(test_platform
	SOURCES
		${SOURCES}
)

target_link_libraries(test_platform
	PRIVATE
		awplatform
		awstring
		awutils
		awtest
		awtest_main)

add_executable(dump_args process/dump_args.c++)
target_link_libraries(dump_args
	PRIVATE
		awutils
		awstring
)
