include(CMakePackageConfigHelpers)
export(EXPORT awlib_targets
	FILE
		"${CMAKE_CURRENT_BINARY_DIR}/awlib/awlibTargets.cmake"
	NAMESPACE
		aw::
)
configure_file(
	awlib/cmake/awlibConfig.cmake
	"${CMAKE_CURRENT_BINARY_DIR}/awlib/awlibConfig.cmake"
	COPYONLY
)

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
		awlib/cmake/awlibConfig.cmake
	DESTINATION
		${ConfigPackageLocation}
	COMPONENT
		Devel
)
