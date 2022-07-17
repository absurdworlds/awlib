cmake_minimum_required(VERSION 3.19)

project(awlib VERSION 0)

if (MSVC)
	# MSVC requires /std:c++latest for some C++20 features
	set(CMAKE_CXX_STANDARD 23)
else()
	set(CMAKE_CXX_STANDARD 20)
endif()

set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(AW_CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/awlib/cmake")

list(APPEND CMAKE_MODULE_PATH ${AW_CMAKE_MODULE_PATH})

if (MSVC)
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


option(AW_MAKE_TESTS "Make tests. Produces a test executable for each library." ON)
option(AW_SPLIT_INCLUDES "Install headers for each library into a separate directory." ON)

if (AW_MAKE_TESTS)
	enable_testing()
endif()

include(aw-common)

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
add_subdirectory(test)

add_subdirectory(archive)
add_subdirectory(thread)
add_subdirectory(doc)

option(AW_ENABLE_GRAPHICS "Enable libawgraphics" ON)
if (AW_ENABLE_GRAPHICS)
	add_subdirectory(graphics)
endif()
add_subdirectory(sound)
add_subdirectory(signals)

include (aw-export)
