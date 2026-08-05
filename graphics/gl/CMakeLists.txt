
option(AW_GL_USE_EGL "Load GL entry points through EGL instead of the platform default (GLX/WGL)." OFF)

if (AW_GL_USE_EGL)
	find_package(OpenGL REQUIRED COMPONENTS OpenGL EGL)
	aw_export_dependency("OpenGL COMPONENTS OpenGL EGL")
else()
	find_package(OpenGL REQUIRED)
	aw_export_dependency(OpenGL)
endif()

aw_add_library(awgl SHARED
	GLOB_HEADERS
	SOURCES
		enum_check.c++
		loader.c++
		gl_46.c++
	EXPORT_NAME
		gl
)

target_compile_definitions(awgl
	PRIVATE
		AW_MODULE_GL_LOADER
)

if (AW_GL_USE_EGL)
	# gl::get_proc() is a header template, so anything compiling against
	# loader.h has to make the same choice awgl was built with.
	target_compile_definitions(awgl
		PUBLIC
			AW_GL_USE_EGL=1)
endif()

target_sources(awgl
  PRIVATE
    include/aw/gl/export.h
)

target_link_libraries(awgl
	PUBLIC
		awalgo
		awutils
		OpenGL::GL)


if (AW_GL_USE_EGL)
	target_link_libraries(awgl
		PRIVATE
			OpenGL::EGL)
elseif (WIN32)
	target_link_libraries(awgl
		PRIVATE
			awplatform)
elseif (APPLE)
elseif (UNIX)
	target_link_libraries(awgl
		PRIVATE
			OpenGL::GLX)
endif()


# Regenerating the loader from the Khronos registry. Run by hand, not part of
# the build: the generated sources are committed, so an ordinary build needs
# neither Lua nor the XML.
#
# The two versions have to agree with the names they are written to, because
# gl_46.h includes gl_33.h by a name worked out from -minversion.
set(AW_GL_BASE_VERSION 3.3)
set(AW_GL_VERSION      4.6)

find_program(AW_LUA NAMES lua lua5.4)
if (AW_LUA)
	set(loadgen ${CMAKE_CURRENT_SOURCE_DIR}/../glloadgen)
	set(gen     ${CMAKE_CURRENT_BINARY_DIR}/generated)
	set(api     ${CMAKE_CURRENT_SOURCE_DIR}/include/aw/gl/api)

	# 3.3 -> 33, matching the file names
	string(REPLACE "." "" base ${AW_GL_BASE_VERSION})
	string(REPLACE "." "" full ${AW_GL_VERSION})

	add_custom_target(regen-gl
		COMMAND ${CMAKE_COMMAND} -E make_directory ${gen}

		COMMAND ${AW_LUA} ${loadgen}/ConvertToLua.lua

		COMMAND ${AW_LUA} ${loadgen}/LoadGen.lua -spec gl -profile core
			-prefix aw -style awlib
			-version ${AW_GL_BASE_VERSION} ${gen}/${base}

		COMMAND ${AW_LUA} ${loadgen}/LoadGen.lua -spec gl -profile core
			-prefix aw -style awlib
			-version ${AW_GL_VERSION} -minversion ${AW_GL_BASE_VERSION}
			${gen}/${full}

		COMMAND ${CMAKE_COMMAND} -DSOURCE=${gen}/gl_${full}.c++
			-P ${CMAKE_CURRENT_SOURCE_DIR}/check-generated.cmake

		COMMAND ${CMAKE_COMMAND} -E copy ${gen}/gl_${base}.h      ${api}/
		COMMAND ${CMAKE_COMMAND} -E copy ${gen}/gl_${base}_enum.h ${api}/
		COMMAND ${CMAKE_COMMAND} -E copy ${gen}/gl_${full}.h      ${api}/
		COMMAND ${CMAKE_COMMAND} -E copy ${gen}/gl_${full}_enum.h ${api}/
		COMMAND ${CMAKE_COMMAND} -E copy ${gen}/gl_${full}.c++    ${CMAKE_CURRENT_SOURCE_DIR}/

		COMMENT "Regenerating the GL loader from ${loadgen}/xml/gl.xml"
		VERBATIM)
endif()
