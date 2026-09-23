file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
#file(GLOB test_data ${CMAKE_CURRENT_BINARY_DIR}/data/*.hdf)

aw_add_test(test_hudf
	SOURCES
		hardening.c++
		reader.c++
		writer.c++
	)
target_link_libraries(test_hudf
	PRIVATE
		awlog
		awio
		awhudf
		awtest
		awtest_main)
