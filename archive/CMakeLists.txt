
aw_add_library(awarchive INTERFACE
	GLOB_HEADERS
	EXPORT_NAME
		archive
)

target_link_libraries(awarchive
	INTERFACE
		awtypes)
