
set(SOURCES)



add_executable(test_meta
	at_index.c++
	eat_paren.c++
	find_index.c++
	find_type.c++
)

target_link_libraries(test_meta
	PRIVATE
		awmeta
		awtest)
