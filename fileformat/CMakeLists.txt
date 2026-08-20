aw_set_if(AW_ENABLE_IMAGE_DEFAULT  AW_ENABLE_GRAPHICS)
aw_set_if(AW_ENABLE_MESH_DEFAULT   AW_ENABLE_GRAPHICS)
aw_set_if(AW_ENABLE_HUDF_DEFAULT   AW_ENABLE_GRAPHICS AND AW_MAKE_DEMOS)

option(AW_ENABLE_HUDF "Enable HuDF data format" ${AW_ENABLE_HUDF_DEFAULT})
if (AW_ENABLE_HUDF)
	add_subdirectory(hudf)
endif()

## Sound file support
option(AW_ENABLE_SOUND "Enable libawsound" OFF)
if (AW_ENABLE_SOUND)
	add_subdirectory(sound)
endif()

## Image file support
option(AW_ENABLE_IMAGE "Enable libawimage" ${AW_ENABLE_IMAGE_DEFAULT})
if (AW_ENABLE_IMAGE)
	add_subdirectory(image)
endif()

## 3D mesh/scene file support
option(AW_ENABLE_MESH "Enable libawmesh" ${AW_ENABLE_MESH_DEFAULT})
if (AW_ENABLE_MESH)
	add_subdirectory(mesh)
endif()
