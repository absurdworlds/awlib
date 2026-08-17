file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# Unit tests
aw_add_test(test_graphics
	SOURCES
		fake_gl.c++
		model.c++
		texture.c++
		vertex_format.c++)

target_link_libraries(test_graphics
	PRIVATE
		awgraphics
		awgl
		awtest
		awtest_main)

# Integration tests
find_package(OpenGL REQUIRED COMPONENTS OpenGL EGL)

aw_add_test(test_graphics_gl
	SOURCES
		gl_context.c++
		shader.c++)

target_link_libraries(test_graphics_gl
	PRIVATE
		awgraphics
		awgl
		awtest
		awtest_main
		OpenGL::EGL)
