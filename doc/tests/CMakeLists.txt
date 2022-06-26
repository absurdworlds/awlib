
set(SOURCES reader.c++) #TODO: writer.c++

add_executable(test_doc ${SOURCES})
target_link_libraries(test_doc
	PRIVATE
		awlog
		awio
		awdoc
		awtest
		awtest_main)
