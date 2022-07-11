
aw_add_library(awsignals INTERFACE
	GLOB_HEADERS
	EXPORT_NAME
		signals
)

target_link_libraries(awsignals
	INTERFACE
		awtypes)
