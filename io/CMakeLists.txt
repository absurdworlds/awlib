aw_add_library(awio INTERFACE
	GLOB_HEADERS
	EXPORT_NAME
		io
)

#target_compile_definitions(awio PRIVATE AW_MODULE_IO)
target_link_libraries(awio
	INTERFACE
		awplatform
		awutils)
