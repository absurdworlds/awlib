set(POSIX_SOURCES)
if(NOT EMSCRIPTEN)
    list(APPEND POSIX_SOURCES process.c++)
endif()

aw_add_test(test_io
	SOURCES
		file.c++
		buffer.c++
		native_file.c++
		mmap_file.c++
		file_stream.c++
		istream_adapter.c++
		memory_stream.c++
		${POSIX_SOURCES}
)

target_link_libraries(test_io
	PRIVATE
		awio
		awstring
		awtest
		awtest_main
)

add_executable(dump_args process/dump_args.c++)
