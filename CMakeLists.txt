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



# TODO: split the project into a set of libraries
set(AW_HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${AW_HEADER_DIR})

add_subdirectory(awlib)
add_subdirectory(meta)
add_subdirectory(algorithm)
add_subdirectory(math)
add_subdirectory(types)
add_subdirectory(platform)
add_subdirectory(utility)
add_subdirectory(string)
add_subdirectory(io)
add_subdirectory(log)
add_subdirectory(test)

add_subdirectory(archive)
add_subdirectory(thread)
add_subdirectory(doc)
add_subdirectory(graphics)
add_subdirectory(sound)
add_subdirectory(signals)
