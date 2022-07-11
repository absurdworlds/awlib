
# awlog interface library: linking with awlog is optional in case user
# wants to provide their own logger implementation
# awlog shared library: provides common logger implementations

aw_add_library(awlog SHARED
	SPLIT_INTERFACE
	GLOB_HEADERS
	SOURCES
		log_base.c++
		ostream_logger.c++
	EXPORT_NAME
		log
)

target_compile_definitions(awlog PRIVATE AW_MODULE_LOG)
target_link_libraries(awlog
	PUBLIC
		awalgo
		awutils)
