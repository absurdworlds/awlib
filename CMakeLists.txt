cmake_minimum_required(VERSION 3.19)

project(awlib VERSION 0)

set(CMAKE_CXX_STANDARD 23)

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if (EMSCRIPTEN)
	set(BUILD_SHARED_LIBS_DEFAULT OFF)
else()
	set(BUILD_SHARED_LIBS_DEFAULT ON)
endif()

option(BUILD_SHARED_LIBS "Build using shared libraries" ${BUILD_SHARED_LIBS_DEFAULT})

set(AW_CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

list(APPEND CMAKE_MODULE_PATH ${AW_CMAKE_MODULE_PATH})

message(STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "Compiler variant: ${CMAKE_CXX_COMPILER_FRONTEND_VARIANT}")

if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	add_compile_options(
		# multicore build by default
		"/MP"
		# disable msvc bugs that were treated as features over the years
		"/permissive-"
		# fix \ treated as esacpe in raw string literals
		"/Zc:preprocessor"
	)
else()
	add_compile_options(
		# falling off the end of a non-void function is UB, not a warning
		"-Werror=return-type"
	)
endif()


if (WIN32)
	set(AW_CAPABILITIES_WIN32 YES)
endif()
if (UNIX)
	set(AW_CAPABILITIES_POSIX YES)
endif()

option(AW_MAKE_TESTS "Make tests. Produces a test executable for each library." ON)
option(AW_MAKE_DEMOS "Build demo programs." OFF)
option(AW_SPLIT_INCLUDES "Install headers for each library into a separate directory." ON)

set(AW_INCLUDE_PREFIX "awlib" CACHE STRING "Prefix for the include directory.")

if (AW_MAKE_TESTS)
	enable_testing()
endif()

include(aw-common)
include(aw-sanitizers)

add_subdirectory(config)
add_subdirectory(base)
add_subdirectory(meta)
add_subdirectory(math)
add_subdirectory(types)
add_subdirectory(platform)

option(AW_ENABLE_ASSERT "Enable aw::assert. If OFF, awlib will be compiled without dependency on aw::assert." ON)
if (AW_ENABLE_ASSERT)
	add_subdirectory(assert)
else()
#TODO: assert stub
endif()

add_subdirectory(utility)
add_subdirectory(string)
add_subdirectory(io)
add_subdirectory(log)
add_subdirectory(test)

add_subdirectory(archive)
add_subdirectory(thread)
add_subdirectory(signals)

# Libraries with extra dependencies
option(AW_ENABLE_GRAPHICS "Enable libawgraphics" OFF)

# Note: has more options inside the makefile,
# must go after AW_ENABLE_GRAPHICS since it reads it to decide the defaults
add_subdirectory(fileformat)

if (AW_ENABLE_GRAPHICS)
	add_subdirectory(graphics)
endif()

option(AW_ENABLE_LUA "Enable libawlua" OFF)
if (AW_ENABLE_LUA)
	add_subdirectory(lua)
endif()

# awstd provides fallbacks for older standards, so it is built separately,
# with its own (much older) value of CMAKE_CXX_STANDARD.
option(AW_ENABLE_AWSTD "Enable libawstd" OFF)
if (AW_ENABLE_AWSTD)
	add_subdirectory(awstd)
endif()


include (aw-export)
