
find_package(glfw3 3.3 REQUIRED)

set(SOURCES renderer.c++ main.c++ camera_controller.c++ scene.c++)

add_executable(rendertest ${HEADERS} ${SOURCES})

target_link_libraries(rendertest
    PUBLIC awio awgraphics awobj awlog awdoc
    PRIVATE
        OpenGL::GL
        glfw)
