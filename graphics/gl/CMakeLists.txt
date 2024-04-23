
find_package(OpenGL REQUIRED)

aw_add_library(awgl STATIC
	GLOB_HEADERS
	SOURCES
		enum_check.c++
		loader.c++
		gl_api.c++
	EXPORT_NAME
		gl
)

target_link_libraries(awgl
	PRIVATE
		OpenGL::GL)


if (WIN32)
	target_link_libraries(awgl
		PRIVATE
			OpenGL::GL
			awplatform)
elseif (APPLE)
	target_link_libraries(awgl
		PRIVATE
			OpenGL::GL)
elseif (UNIX)
	target_link_libraries(awgl
		PRIVATE
			OpenGL::OpenGL
			OpenGL::GLX)
endif()
