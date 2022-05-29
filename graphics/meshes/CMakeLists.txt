find_package(PNG REQUIRED)

file(GLOB_RECURSE HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
set(SOURCES obj_loader.c++ mtl_loader.c++ png_loader.c++ shared.h)

add_library(awobj STATIC ${HEADERS} ${SOURCES})
target_include_directories(awobj PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

 #AW_MANUAL_TEST
#target_compile_definitions(awobj PRIVATE AW_MODULE_GRAPHICS)

target_link_libraries(awobj
    PUBLIC  awio awlog
    PRIVATE PNG::PNG)
