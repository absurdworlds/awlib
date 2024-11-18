
find_package(OpenGL REQUIRED)

aw_add_library(awgl SHARED
	GLOB_HEADERS
	SOURCES
		enum_check.c++
		loader.c++
		gl_api.c++
	EXPORT_NAME
		gl
)

target_compile_definitions(awgl
	PRIVATE
		AW_MODULE_GL_LOADER
)

target_sources(awgl
  PRIVATE
    include/aw/gl/export.h
)

target_link_libraries(awgl
	PUBLIC
		awalgo
		awutils
		OpenGL::GL)


if (WIN32)
	target_link_libraries(awgl
		PRIVATE
			awplatform)
elseif (APPLE)
elseif (UNIX)
	target_link_libraries(awgl
		PRIVATE
			OpenGL::GLX)
endif()
