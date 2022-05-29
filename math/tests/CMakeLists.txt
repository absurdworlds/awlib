
set(SOURCES
    functions.c++
    bitmath.c++
    angle.c++
    orientation.c++
    quaternion.c++
    vector.c++
    matrix.c++
    matrix3.c++
    matrix4.c++)

add_executable(test_math ${SOURCES})
target_link_libraries(test_math
    PRIVATE
        awmath
        awtest)
