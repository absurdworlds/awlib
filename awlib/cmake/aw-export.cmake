include(CMakePackageConfigHelpers)
export(EXPORT awlib_targets
	FILE
		"${CMAKE_CURRENT_BINARY_DIR}/awlib/awlibTargets.cmake"
	NAMESPACE
		aw::
)

set(AW_EXPORT_FILE "${CMAKE_CURRENT_BINARY_DIR}/awlib/awlibConfig.cmake")

configure_file(
	awlib/cmake/awlibConfig.cmake
	"${CMAKE_CURRENT_BINARY_DIR}/awlib/awlibConfig.cmake"
	COPYONLY
)

get_property(DEPS GLOBAL PROPERTY AW_EXPORT_DEPENDENCIES)
if (DEPS)
	file(APPEND ${AW_EXPORT_FILE} "\ninclude(CMakeFindDependencyMacro)\n\n")
	foreach(dep ${DEPS})
		file(APPEND ${AW_EXPORT_FILE} "find_dependency(${dep})\n")
	endforeach()
endif()

set(ConfigPackageLocation lib/cmake/awlib)

install(EXPORT
	awlib_targets
	FILE
		awlibTargets.cmake
	NAMESPACE
		aw::
	DESTINATION
		${ConfigPackageLocation}
)
install(
	FILES
		awlib/cmake/aw-common.cmake
		${AW_EXPORT_FILE}
	DESTINATION
		${ConfigPackageLocation}
	COMPONENT
		Devel
)
