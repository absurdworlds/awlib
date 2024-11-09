#TODO: switches for each individual file format

find_package(PNG REQUIRED)

aw_export_dependency(PNG)

aw_add_library(awimage STATIC
	GLOB_HEADERS
	SOURCES
		png_loader.c++
	EXPORT_NAME
		image)

target_link_libraries(awimage
	PUBLIC
		awio
		awlog
		awstring
	PRIVATE
		PNG::PNG)
