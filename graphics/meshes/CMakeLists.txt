find_package(PNG REQUIRED)

aw_add_library(awobj STATIC
	GLOB_HEADERS
	SOURCES
		obj_loader.c++ mtl_loader.c++ png_loader.c++ shared.h
	EXPORT_NAME
		graphics-importer)

 #AW_MANUAL_TEST
#target_compile_definitions(awobj PRIVATE AW_MODULE_GRAPHICS)

aw_export_dependency(PNG)

target_link_libraries(awobj
    PUBLIC  awio awlog
    PRIVATE PNG::PNG)
