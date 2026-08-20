
aw_add_library(awmesh STATIC
	GLOB_HEADERS
	SOURCES
		obj_loader.c++ mtl_loader.c++ shared.h
	EXPORT_NAME
		mesh)

target_link_libraries(awmesh
	PUBLIC
		awio
		awlog
		awstring)
