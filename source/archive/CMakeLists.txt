
file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)

add_library(awarchive INTERFACE ${HEADERS})
target_include_directories(awarchive INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

#set_target_properties(awalgorithm PROPERTIES LINKER_LANGUAGE CXX)

add_subdirectory(test) #TODO: rename to tests for consistency
