cmake_minimum_required(VERSION 3.19)

project(awlib)

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

if (MSVC)
	add_compile_options(
		# multicore build by default
		"/MP"
		# disable msvc bugs that were treated as features over the years
		"/permissive-"
		# fix \ treates as esacpe in raw string literals
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


add_subdirectory(awlib)
add_subdirectory(meta)
add_subdirectory(algorithm)
add_subdirectory(math)
add_subdirectory(types)
add_subdirectory(platform)
add_subdirectory(assert)
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
