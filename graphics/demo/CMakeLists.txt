
find_package(glfw3 3.3 REQUIRED)

set(SOURCES renderer.c++ main.c++ camera_controller.c++ scene.c++)

add_executable(awgraphics-demo ${HEADERS} ${SOURCES})

target_link_libraries(awgraphics-demo
    PUBLIC
        awio
        awgraphics
        awmesh
        awimage
        awlog
        awhudf
        awtypes
    PRIVATE
        glfw)
