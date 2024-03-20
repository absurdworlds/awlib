aw_add_test(test_io
	SOURCES
		buffer.cpp
		file.cpp
		file_stream.cpp
		istream_adapter.cpp)

target_link_libraries(test_io
	PRIVATE
		awio
		awtest
		awtest_main
)
