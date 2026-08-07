aw_add_test(test_mesh
	SOURCES
		obj_loader.c++)

target_link_libraries(test_mesh
	PRIVATE
		awmesh
		awtest
		awtest_main)
