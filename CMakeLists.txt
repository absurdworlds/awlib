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

set(AW_CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/awlib/cmake")

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
endif()


if (WIN32)
	set(AW_CAPABILITIES_WIN32 YES)
endif()
if (UNIX)
	set(AW_CAPABILITIES_POSIX YES)
endif()

# Neither means a bare-metal target (CMAKE_SYSTEM_NAME=Generic): there is no
# OS, so no threads and no signals, and usually no exceptions either.
if (NOT AW_CAPABILITIES_WIN32 AND NOT AW_CAPABILITIES_POSIX)
	set(AW_BAREMETAL YES)
endif()

if (AW_BAREMETAL)
	# There is nowhere to run the test executables, and the test framework
	# itself needs exceptions and POSIX signals.
	set(AW_MAKE_TESTS_DEFAULT OFF)
else()
	set(AW_MAKE_TESTS_DEFAULT ON)
endif()

option(AW_MAKE_TESTS "Make tests. Produces a test executable for each library." ${AW_MAKE_TESTS_DEFAULT})
option(AW_MAKE_DEMOS "Build demo programs." OFF)
option(AW_SPLIT_INCLUDES "Install headers for each library into a separate directory." ON)

set(AW_INCLUDE_PREFIX "awlib" CACHE STRING "Prefix for the include directory.")

if (AW_MAKE_TESTS)
	enable_testing()
endif()

include(aw-common)
include(aw-sanitizers)

add_subdirectory(awlib)
add_subdirectory(meta)
add_subdirectory(algorithm)
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
if (NOT AW_BAREMETAL)
	add_subdirectory(test)
endif()

add_subdirectory(archive)
# libawthread is built on top of std::thread, which a bare-metal toolchain
# does not provide.
if (NOT AW_BAREMETAL)
	add_subdirectory(thread)
endif()
add_subdirectory(signals)

add_subdirectory(fileformat)

# Libraries with extra dependencies
option(AW_ENABLE_GRAPHICS "Enable libawgraphics" OFF)
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
