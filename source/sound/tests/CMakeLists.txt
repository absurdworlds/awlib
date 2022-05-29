
set(SOURCES wav_reader.cpp) # TODO: .c++

add_executable(test_wav ${SOURCES})
target_link_libraries(test_wav  awaudio awio awplatform)

# TODO: install the test file
