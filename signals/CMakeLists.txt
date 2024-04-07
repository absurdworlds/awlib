
aw_add_library(awsignals INTERFACE
	VERSION 2.0
	GLOB_HEADERS
	EXPORT_NAME
		signals
)

target_link_libraries(awsignals
	INTERFACE
		awtypes)
