find_package(PNG REQUIRED)

file(GLOB_RECURSE SOURCES obj_loader.c++ mtl_loader.c++ png_loader.c++ shared.h)

add_library(awobj STATIC ${HEADERS} ${SOURCES})

 #AW_MANUAL_TEST
#target_compile_definitions(awobj PRIVATE AW_MODULE_GRAPHICS)

target_link_libraries(awobj
    PUBLIC  awio awlog
    PRIVATE PNG::PNG)
