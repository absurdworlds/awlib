
aw_add_library(awtypes INTERFACE
	GLOB_HEADERS
	EXPORT_NAME
		types
)

target_link_libraries(awtypes
	INTERFACE
		awmeta)
