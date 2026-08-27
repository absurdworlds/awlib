aw_add_test(test_math
	SOURCES
	functions.c++
	numeric.c++
	angle.c++
	orientation.c++
	quaternion.c++
	vector.c++
	matrix.c++
	matrix3.c++
	matrix4.c++)

target_link_libraries(test_math
	PRIVATE
		awmath
		awtest
		awtest_main)
