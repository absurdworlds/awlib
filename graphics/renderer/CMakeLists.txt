
set(awgraphics_SOURCES
	gl3/shader.c++
	gl3/program.c++
	gl3/uniform.c++
	gl3/resources.c++
	gl3/texture.c++
	gl3/model.c++
	gl3/material.c++
	gl3/render_context.c++)

aw_add_library(awgraphics SHARED
	GLOB_HEADERS
	SOURCES
		${awgraphics_SOURCES}
	EXPORT_NAME
		graphics)

target_compile_definitions(awgraphics
	PRIVATE
		AW_MODULE_GRAPHICS
)

target_link_libraries(awgraphics
	PUBLIC
		awio
		awmath
		awobj
		awgl)
