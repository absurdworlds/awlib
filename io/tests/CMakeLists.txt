aw_add_test(test_io
	SOURCES
		file.cpp
		buffer.cpp
		native_file.cpp
		mmap_file.cpp
		file_stream.cpp
		process.c++
		istream_adapter.cpp)

target_link_libraries(test_io
	PRIVATE
		awio
		awtest
		awtest_main
)

add_executable(dump_args process/dump_args.c++)
