add_executable(awhudf-demo hudf_dump.c++)

target_link_libraries(awhudf-demo
	PRIVATE
		awlog
		awio
		awhudf)
