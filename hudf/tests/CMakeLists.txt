file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
#file(GLOB test_data ${CMAKE_CURRENT_BINARY_DIR}/data/*.hdf)

aw_add_test(test_doc
	PARAMS
		data/messages.hdf
		data/settings.hdf
		data/sotank.hdf
		data/sphere5.hdf
		data/test.hdf
	SOURCES
		reader.c++
		#TODO: writer.c++
	)

add_test(
	NAME test_doc_fail
	COMMAND test_doc data/invalid.hdf)
set_property(TEST test_doc_fail PROPERTY WILL_FAIL ON)

target_link_libraries(test_doc
	PRIVATE
		awlog
		awio
		awdoc
		awtest
		awtest_main)
