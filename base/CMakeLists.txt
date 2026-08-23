aw_add_library(awbase INTERFACE
	GLOB_HEADERS
	EXPORT_NAME
		base
)

target_link_libraries(awbase
	INTERFACE
		awconfig)

# The parts of base are still named, so that a consumer can say which of
# them it means, even though they are all the same library now.
add_library(awalgo INTERFACE)
target_link_libraries(awalgo INTERFACE awbase)
set_target_properties(awalgo PROPERTIES EXPORT_NAME algorithm)

add_library(awmeta INTERFACE)
target_link_libraries(awmeta INTERFACE awbase)
set_target_properties(awmeta PROPERTIES EXPORT_NAME meta)

add_library(awtypes INTERFACE)
target_link_libraries(awtypes INTERFACE awbase)
set_target_properties(awtypes PROPERTIES EXPORT_NAME types)

install(
	TARGETS
		awalgo
		awmeta
		awtypes
	EXPORT
		${AW_PROJECT_NAME}_targets
)
