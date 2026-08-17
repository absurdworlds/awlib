add_executable(awutils-demo arg_parser.c++)

target_link_libraries(awutils-demo
	PRIVATE
		awutils)
