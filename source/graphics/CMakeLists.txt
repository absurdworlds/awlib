
find_package(OpenGL REQUIRED)

file(GLOB_RECURSE awgraphics_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
file(GLOB_RECURSE awgraphics_SOURCES
    gl/loader.c++ gl/gl_api.c++ gl/enum_check.c++
    gl3/shader.c++ gl3/program.c++ gl3/uniform.c++ gl3/resources.c++
    gl3/texture.c++ gl3/model.c++ gl3/material.c++ gl3/render_context.c++)

add_library(awgraphics SHARED ${awgraphics_HEADERS} ${awgraphics_SOURCES})

target_compile_definitions(awgraphics PRIVATE AW_MODULE_GRAPHICS)
target_include_directories(awgraphics PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(awgraphics
    PUBLIC awio awobj
    PRIVATE
        OpenGL::GL)

if (WIN32)
    target_link_libraries(awgraphics
        PRIVATE
            OpenGL::GL)
endif()

if (UNIX)
    target_link_libraries(awgraphics
        PRIVATE
            OpenGL::OpenGL
            OpenGL::GLX)
endif()

add_subdirectory(test)
add_subdirectory(meshes)
