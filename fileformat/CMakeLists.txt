option(AW_ENABLE_HUDF "Enable HuDF data format" OFF)
if (AW_ENABLE_HUDF)
	add_subdirectory(hudf)
endif()

## Sound file support
option(AW_ENABLE_SOUND "Enable libawsound" OFF)
if (AW_ENABLE_SOUND)
	add_subdirectory(sound)
endif()
