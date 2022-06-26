
set(SOURCES  split.c++ join.c++ common_prefix.c++)

add_executable(test_algo ${SOURCES})
target_link_libraries(test_algo
	PRIVATE
		awalgo
		awtest
		awtest_main)
