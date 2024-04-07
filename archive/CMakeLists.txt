
aw_add_library(awarchive INTERFACE
	VERSION 3.0
	GLOB_HEADERS
	EXPORT_NAME
		archive
)

target_link_libraries(awarchive
	INTERFACE
		awtypes)
