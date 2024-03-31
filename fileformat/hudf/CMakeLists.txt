aw_add_library(awhudf SHARED
	GLOB_HEADERS
	SOURCES
		lexer.c++
		parser.c++
		writer.c++
		utility.c++
		document.c++
	EXPORT_NAME
		hudf
)

target_compile_definitions(awhudf PRIVATE AW_MODULE_HUDF)
target_link_libraries(awhudf
	PUBLIC
		awlog_interface
		awutils
		awio
		awstring)
