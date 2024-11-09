option(AW_ENABLE_HUDF "Enable HuDF data format" OFF)
if (AW_ENABLE_HUDF)
	add_subdirectory(hudf)
endif()

## Sound file support
option(AW_ENABLE_SOUND "Enable libawsound" OFF)
if (AW_ENABLE_SOUND)
	add_subdirectory(sound)
endif()

## Image file support
option(AW_ENABLE_IMAGE "Enable libawimage" OFF)
if (AW_ENABLE_IMAGE)
	add_subdirectory(image)
endif()

## 3D mesh/scene file support
option(AW_ENABLE_MESH "Enable libawmesh" OFF)
if (AW_ENABLE_MESH)
	add_subdirectory(mesh)
endif()
