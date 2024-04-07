
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

# TODO: install the test file
