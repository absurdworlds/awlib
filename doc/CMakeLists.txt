aw_add_library(awdoc SHARED
	GLOB_HEADERS
	SOURCES
		lexer.c++
		parser.c++
		writer.c++
		utility.c++
		document.c++
	EXPORT_NAME
		doc
)

target_compile_definitions(awdoc PRIVATE AW_MODULE_DOC)
target_link_libraries(awdoc
	PUBLIC
		awlog_interface
		awutils
		awio)
