set(SOURCES os_version.c++ demangle.c++)

aw_add_library(awplatform SHARED
	GLOB_HEADERS
	SOURCES
		${SOURCES}
	EXPORT_NAME
		platform
)

target_compile_definitions(awplatform PRIVATE AW_MODULE_PLATFORM)
target_link_libraries(awplatform
	PUBLIC
		awconfig
		awtypes
	PRIVATE
		awalgo
		awutils)

if (WIN32)
	target_link_libraries(awplatform
	PRIVATE
		DbgHelp
	)
endif()
