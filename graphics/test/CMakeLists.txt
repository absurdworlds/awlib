
find_package(glfw3 3.3 REQUIRED)
find_package(yaml-cpp REQUIRED)

set(SOURCES renderer.c++ main.c++ camera_controller.c++ scene.c++)

add_executable(rendertest ${HEADERS} ${SOURCES})

target_link_libraries(rendertest
	PUBLIC
		awio
		awgraphics
		awobj
		awlog
		awtypes
	PRIVATE
		OpenGL::GL
		yaml-cpp
		glfw)
