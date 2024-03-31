
aw_add_library(awutils SHARED
	GLOB_HEADERS
	SOURCES
		argv_parser.c++
		murmur_hash3.c++
	EXPORT_NAME
		utility
)

target_compile_definitions(awutils PRIVATE AW_MODULE_UTILS)
target_link_libraries(awutils
	PUBLIC
		aw
		awtypes
		awalgo
		awmath # TODO: maybe get rid of bitmath?
)
