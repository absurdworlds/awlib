
aw_add_library(awsound SHARED
	VERSION 1.0.0
	GLOB_HEADERS
	SOURCES
		wav_reader.c++
		chunks.h
	EXPORT_NAME
		sound
	)

target_compile_definitions(awsound PRIVATE AW_MODULE_SOUND)
target_link_libraries(awsound
	PUBLIC
		awlog_interface
		awio)
