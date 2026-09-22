aw_add_test(test_io
	SOURCES
		file.c++
		buffered_file.c++
		buffer.c++
		file_stream.c++
		istream_adapter.c++
		memory_stream.c++
)

target_link_libraries(test_io
	PRIVATE
		awio
		awstring
		awtest
		awtest_main
)
