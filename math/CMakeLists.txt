
aw_add_library(awmath INTERFACE
	GLOB_HEADERS
	EXPORT_NAME
		math
)

target_link_libraries(awmath
	INTERFACE
		awtypes)
