aw_add_library(awbase INTERFACE
	EXPORT_NAME
		base
)

target_link_libraries(awbase
	INTERFACE
		awconfig)
