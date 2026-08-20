add_executable(awmesh-demo obj_dump.c++)

target_link_libraries(awmesh-demo
	PRIVATE
		awmesh)
