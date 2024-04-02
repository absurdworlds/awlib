
find_package(OpenGL REQUIRED)

set(awgraphics_SOURCES
	gl/loader.c++
	gl/gl_api.c++
	gl/enum_check.c++
	gl3/shader.c++
	gl3/program.c++
	gl3/uniform.c++
	gl3/resources.c++
	gl3/texture.c++
	gl3/model.c++
	gl3/material.c++
	gl3/render_context.c++
)

aw_add_library(awgraphics SHARED
	GLOB_HEADERS
	SOURCES
		${awgraphics_SOURCES}
	EXPORT_NAME
		graphics
)

target_compile_definitions(awgraphics
	PRIVATE
		AW_MODULE_GRAPHICS
)

if (WIN32)
	set(AW_OPENGL_LIBS
		OpenGL::GL
		awplatform
	)
elseif (APPLE)
	set(AW_OPENGL_LIBS
		OpenGL::GL
	)
elseif (UNIX)
	set(AW_OPENGL_LIBS
		OpenGL::GL
		OpenGL::GLX
	)
endif()


target_link_libraries(awgraphics
	PUBLIC
		awio
		awmath
		awobj
	PRIVATE
		${AW_OPENGL_LIBS}
)

add_subdirectory(test)
add_subdirectory(meshes)
