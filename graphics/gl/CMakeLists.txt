
option(AW_GL_USE_EGL "Load GL entry points through EGL instead of the platform default (GLX/WGL)." OFF)

if (AW_GL_USE_EGL)
	find_package(OpenGL REQUIRED COMPONENTS OpenGL EGL)
	aw_export_dependency("OpenGL COMPONENTS OpenGL EGL")
else()
	find_package(OpenGL REQUIRED)
	aw_export_dependency(OpenGL)
endif()

aw_add_library(awgl SHARED
	GLOB_HEADERS
	SOURCES
		enum_check.c++
		loader.c++
		gl_46.c++
	EXPORT_NAME
		gl
)

target_compile_definitions(awgl
	PRIVATE
		AW_MODULE_GL_LOADER
)

if (AW_GL_USE_EGL)
	# gl::get_proc() is a header template, so anything compiling against
	# loader.h has to make the same choice awgl was built with.
	target_compile_definitions(awgl
		PUBLIC
			AW_GL_USE_EGL=1)
endif()

target_sources(awgl
  PRIVATE
    include/aw/gl/export.h
)

target_link_libraries(awgl
	PUBLIC
		awalgo
		awutils
		OpenGL::GL)


if (AW_GL_USE_EGL)
	target_link_libraries(awgl
		PRIVATE
			OpenGL::EGL)
elseif (WIN32)
	target_link_libraries(awgl
		PRIVATE
			awplatform)
elseif (APPLE)
elseif (UNIX)
	target_link_libraries(awgl
		PRIVATE
			OpenGL::GLX)
endif()
