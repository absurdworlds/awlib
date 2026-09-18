
aw_add_library(awio INTERFACE
	GLOB_HEADERS
	EXPORT_NAME
		io
)

target_link_libraries(awio
	INTERFACE
		awplatform)
