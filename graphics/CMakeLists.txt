
find_package(OpenGL REQUIRED)

set(awgraphics_SOURCES
    gl/loader.c++ gl/gl_api.c++ gl/enum_check.c++
    gl3/shader.c++ gl3/program.c++ gl3/uniform.c++ gl3/resources.c++
    gl3/texture.c++ gl3/model.c++ gl3/material.c++ gl3/render_context.c++)

aw_add_library(awgraphics SHARED
    GLOB_HEADERS
    SOURCES
    ${awgraphics_SOURCES})

target_link_libraries(awgraphics
    PUBLIC
        awio
        awmath
        awobj
    PRIVATE
        OpenGL::GL)

if (WIN32)
    target_link_libraries(awgraphics
        PRIVATE
            OpenGL::GL
		awplatform)
elseif (APPLE)
    target_link_libraries(awgraphics
        PRIVATE
            OpenGL::GL)
elseif (UNIX)
    target_link_libraries(awgraphics
        PRIVATE
            OpenGL::OpenGL
            OpenGL::GLX)
endif()

add_subdirectory(test)
add_subdirectory(meshes)
