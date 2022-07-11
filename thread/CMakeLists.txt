aw_add_library(awthread SHARED
	GLOB_HEADERS
	SOURCES
		worker.c++
	EXPORT_NAME
		thread
)

target_compile_definitions(awthread PRIVATE AW_MODULE_THREAD)
target_link_libraries(awthread aw)
