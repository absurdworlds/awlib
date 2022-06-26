
set(SOURCES)



add_executable(test_meta
	at_index.c++
	find_index.c++
	find_type.c++
	source_location.c++
	pp/macro.c++
	pp/tuple.c++
	pp/foldl.c++
	pp/foldr.c++
	pp/reverse.c++
	pp/eat_paren.c++
	pp/struct.c++
)

target_link_libraries(test_meta
	PRIVATE
		awmeta
		awtest)
