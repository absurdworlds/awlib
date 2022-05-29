
file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)

add_library(awalgo INTERFACE ${HEADERS})
target_include_directories(awalgo INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

#set_target_properties(awalgorithm PROPERTIES LINKER_LANGUAGE CXX)

add_subdirectory(tests)
