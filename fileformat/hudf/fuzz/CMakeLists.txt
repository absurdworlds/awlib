aw_add_fuzzer(fuzz_hudf
	SOURCES parse.c++
	CORPUS  corpus)

target_link_libraries(fuzz_hudf
	PRIVATE
		awio
		awhudf)
