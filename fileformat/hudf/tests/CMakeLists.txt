file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
#file(GLOB test_data ${CMAKE_CURRENT_BINARY_DIR}/data/*.hdf)

aw_add_test(test_doc_reader
	PARAMS
		data/messages.hdf
		data/settings.hdf
		data/sotank.hdf
		data/sphere5.hdf
		data/test.hdf
	SOURCES
		reader.c++
	)
target_link_libraries(test_doc_reader
	PRIVATE
		awlog
		awio
		awhudf
		awtest
		awtest_main)

add_test(
	NAME test_hudf_fail
	COMMAND test_doc_reader data/invalid.hdf)
set_property(TEST test_hudf_fail PROPERTY WILL_FAIL ON)

aw_add_test(test_doc_writer
	SOURCES
		writer.c++
	)
target_link_libraries(test_doc_writer
	PRIVATE
		awhudf
		awtest
		awtest_main)
