
file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)

add_library(awtypes INTERFACE ${HEADERS})
target_include_directories(awtypes INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

#set_target_properties(awtypes PROPERTIES LINKER_LANGUAGE CXX)

add_subdirectory(tests)
