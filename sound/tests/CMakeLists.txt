
set(SOURCES wav_reader.cpp) # TODO: .c++

add_executable(test_wav ${SOURCES})
target_link_libraries(test_wav
	PRIVATE
		awaudio
		awio
		awplatform
		awtest
		awtest_main)

# TODO: install the test file
