if (NOT (AW_ENABLE_IMAGE AND AW_ENABLE_MESH))
	message(FATAL_ERROR "AW_ENABLE_GRAPHICS requires AW_ENABLE_IMAGE and AW_ENABLE_MESH")
endif()

set(awgraphics_SOURCES
	gl3/log.c++
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
		awimage # TODO: remove
		awmesh  # TODO: remove
		awgl)
