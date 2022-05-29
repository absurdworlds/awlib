cmake_minimum_required(VERSION 3.19)

project(awlib)

set(CMAKE_CXX_STANDARD 23)

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

add_subdirectory(source/archive)
add_subdirectory(source/algorithm)
add_subdirectory(source/math)
add_subdirectory(source/types)
add_subdirectory(source/platform)
add_subdirectory(source/test)
add_subdirectory(source/string)
add_subdirectory(source/utility)
add_subdirectory(source/thread)
add_subdirectory(source/io)
add_subdirectory(source/log)
add_subdirectory(source/doc)
add_subdirectory(source/graphics)
add_subdirectory(source/sound)
