cmake_minimum_required (VERSION 3.0)

project(hrengin)

include_directories(${CMAKE_CURRENT_LIST_DIR}/include)

add_subdirectory(tests)
add_subdirectory(source)
