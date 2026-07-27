#
# awstd is not built as a part of awlib by default: it targets old C++
# standards, whereas the rest of awlib is built as C++23.
#
# It can be built on its own:
#     cmake -S awstd -B build/awstd && cmake --build build/awstd
# or as a part of an awlib build, by passing -DAW_ENABLE_AWSTD=ON.
#
cmake_minimum_required(VERSION 3.19)

project(awstd VERSION 0 LANGUAGES CXX)

if (CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
	set(AWSTD_STANDALONE ON)
else()
	set(AWSTD_STANDALONE OFF)
endif()

set(AWSTD_CXX_STANDARD "98" CACHE STRING
	"C++ standard used to build awstd. The fallbacks only make sense for the older ones.")
set_property(CACHE AWSTD_CXX_STANDARD PROPERTY STRINGS 98 11 14 17 20 23)

if (DEFINED AW_MAKE_TESTS)
	set(AWSTD_MAKE_TESTS_DEFAULT ${AW_MAKE_TESTS})
else()
	set(AWSTD_MAKE_TESTS_DEFAULT ${AWSTD_STANDALONE})
endif()

option(AWSTD_MAKE_TESTS "Make awstd tests." ${AWSTD_MAKE_TESTS_DEFAULT})

# CXX_STANDARD values are years modulo a century, and 98 is the smallest
# of them, so turn them into full years to be able to compare them
if (AWSTD_CXX_STANDARD EQUAL 98)
	set(AWSTD_CXX_YEAR 1998)
else()
	math(EXPR AWSTD_CXX_YEAR "2000 + ${AWSTD_CXX_STANDARD}")
endif()

# MSVC has no way to select anything older than C++14
if (MSVC AND AWSTD_CXX_YEAR LESS 2014)
	message(STATUS "awstd: MSVC does not support C++${AWSTD_CXX_STANDARD}, building as C++14")
	set(AWSTD_CXX_STANDARD 14)
	set(AWSTD_CXX_YEAR 2014)
endif()

message(STATUS "awstd: building as C++${AWSTD_CXX_STANDARD}")

#
# awstd uses awlib's <aw/config.h> for platform detection.
# When built inside the awlib tree, it is right next to us,
# otherwise an installed awlib is looked up.
#
if (TARGET awconfig)
	set(AWSTD_CONFIG_TARGET awconfig)
else()
	find_path(AWSTD_AWLIB_INCLUDE_DIR
		NAMES aw/config.h
		HINTS "${PROJECT_SOURCE_DIR}/../awlib/include"
		DOC "Directory containing awlib's <aw/config.h>")

	if (NOT AWSTD_AWLIB_INCLUDE_DIR)
		find_package(awlib REQUIRED)
		set(AWSTD_CONFIG_TARGET aw::config)
	endif()
endif()

# awlib sets these itself, we only need them for a standalone build
if (WIN32)
	set(AW_CAPABILITIES_WIN32 YES)
endif()
if (UNIX)
	set(AW_CAPABILITIES_POSIX YES)
endif()

set(AWSTD_SOURCES
	source/C++98/fspath.c++
)

# std::filesystem fallback operations are written in C++14
if (NOT AWSTD_CXX_YEAR LESS 2014)
	if (AW_CAPABILITIES_WIN32)
		list(APPEND AWSTD_SOURCES source/C++14/win32_fsops.c++)
	elseif (AW_CAPABILITIES_POSIX)
		list(APPEND AWSTD_SOURCES source/C++14/posix_fsops.c++)
	endif()
endif()

file(GLOB_RECURSE AWSTD_HEADERS "${PROJECT_SOURCE_DIR}/include/*.h")

add_library(awstd ${AWSTD_SOURCES} ${AWSTD_HEADERS})

set_target_properties(awstd
	PROPERTIES
		CXX_STANDARD ${AWSTD_CXX_STANDARD}
		CXX_STANDARD_REQUIRED ON
		CXX_EXTENSIONS OFF
		CXX_VISIBILITY_PRESET hidden
		POSITION_INDEPENDENT_CODE ON
		VERSION ${PROJECT_VERSION}
		SOVERSION ${PROJECT_VERSION_MAJOR}
)

target_include_directories(awstd
	PUBLIC
		$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:include>
)

if (AWSTD_CONFIG_TARGET)
	target_link_libraries(awstd PUBLIC ${AWSTD_CONFIG_TARGET})
else()
	target_include_directories(awstd PUBLIC $<BUILD_INTERFACE:${AWSTD_AWLIB_INCLUDE_DIR}>)
endif()

target_compile_definitions(awstd PRIVATE AWSTD_MODULE_FS)

if (NOT BUILD_SHARED_LIBS)
	target_compile_definitions(awstd PUBLIC AW_STATIC_BUILD)
endif()

if (MSVC)
	# without this __cplusplus is always reported as 199711L
	target_compile_options(awstd PUBLIC "/Zc:__cplusplus")
endif()

#
# The headers named after standard ones (<string_view>, <filesystem>, ...)
# live in include/awstd, so that adding it to the include path makes them
# available under their standard names. See Readme.md for the caveats.
#
add_library(awstd_shims INTERFACE)
set_property(TARGET awstd_shims PROPERTY EXPORT_NAME shims)
target_include_directories(awstd_shims
	INTERFACE
		$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/awstd>
		$<INSTALL_INTERFACE:include/awstd>
)
target_link_libraries(awstd_shims INTERFACE awstd)

add_library(awstd::awstd ALIAS awstd)
add_library(awstd::shims ALIAS awstd_shims)

if (AWSTD_MAKE_TESTS)
	enable_testing()
	add_subdirectory(tests)
endif()

install(
	TARGETS awstd awstd_shims
	EXPORT awstd_targets
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	RUNTIME DESTINATION bin
)

install(
	DIRECTORY "${PROJECT_SOURCE_DIR}/include/"
	DESTINATION include
	COMPONENT Devel
)

install(
	EXPORT awstd_targets
	FILE awstdTargets.cmake
	NAMESPACE awstd::
	DESTINATION lib/cmake/awstd
)

if (AWSTD_CONFIG_TARGET)
	set(AWSTD_CONFIG_DEPENDENCY "include(CMakeFindDependencyMacro)\nfind_dependency(awlib)")
else()
	set(AWSTD_CONFIG_DEPENDENCY "")
endif()

configure_file(
	"${PROJECT_SOURCE_DIR}/cmake/awstdConfig.cmake.in"
	"${PROJECT_BINARY_DIR}/awstdConfig.cmake"
	@ONLY
)

install(
	FILES "${PROJECT_BINARY_DIR}/awstdConfig.cmake"
	DESTINATION lib/cmake/awstd
	COMPONENT Devel
)
