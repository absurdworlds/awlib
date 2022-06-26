
set(SOURCES
    main.c++)

add_library(awtest_main STATIC ${SOURCES})
target_link_libraries(awtest_main
    PUBLIC awtest)
