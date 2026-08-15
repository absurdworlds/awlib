
# The test opens this by name, and aw_add_test() runs it from the binary
# directory. Same as the hudf tests do with their data/.
file(COPY glass.wav DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

aw_add_test(test_wav
	SOURCES
		wav_reader.c++)
target_link_libraries(test_wav
	PRIVATE
		awsound
		awio
		awplatform
		awtest
		awtest_main)
