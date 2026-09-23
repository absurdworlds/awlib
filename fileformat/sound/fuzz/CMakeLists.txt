aw_add_fuzzer(fuzz_wav
	SOURCES read.c++
	CORPUS  corpus)

target_link_libraries(fuzz_wav
	PRIVATE
		awio
		awsound)
