if (NOT AW_PROJECT_NAME)
	set(AW_PROJECT_NAME ${PROJECT_NAME})
endif()

macro(aw_export_dependency DEP)
	set_property(GLOBAL APPEND PROPERTY AW_EXPORT_DEPENDENCIES ${DEP})
endmacro()

# Options:
# SPLIT_INTERFACE
#     Generate an additional LIB_interface target which contains public headers
# HEADERS <list>
#     Specify public header files
# GLOB_HEADERS
#     Glob headers in the standard include path instead of providing the HEADERS manually
# EXPORT_NAME <name>
#     Alias for the exported target
function(aw_add_library NAME TYPE)
	set(options GLOB_HEADERS SPLIT_INTERFACE)
	set(arguments EXPORT_NAME)
	set(multivalue HEADERS SOURCES)
	cmake_parse_arguments(PARSE_ARGV 1 ARG "${options}" "${arguments}" "${multivalue}")

	if (ARG_GLOB_HEADERS)
		if (ARG_HEADERS)
			message(FATAL_ERROR "Cannot use GLOB_HEADERS with manually specified HEADERS")
		endif()
		file(GLOB_RECURSE ARG_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)
	endif()

	add_library(${NAME} ${TYPE} ${ARG_HEADERS} ${ARG_SOURCES})

	if ("${TYPE}" STREQUAL "INTERFACE")
		set(INCLUDE_TYPE "INTERFACE")
	else()
		set(INCLUDE_TYPE "PUBLIC")
		set_target_properties(${NAME} PROPERTIES LINKER_LANGUAGE CXX)
	endif()

	if (UNIX)
		set_target_properties(${NAME}
			PROPERTIES
				VERSION ${CMAKE_PROJECT_VERSION}
				SOVERSION ${PROJECT_VERSION_MAJOR} )
	endif()

	set(EXPORT_TARGETS ${NAME})

	if (ARG_SPLIT_INTERFACE)
		set(INTERFACE_LIB ${NAME}_interface)

		add_library(${INTERFACE_LIB} INTERFACE)

		target_link_libraries(${NAME} ${INCLUDE_TYPE} ${INTERFACE_LIB})

		set(INCLUDE_TYPE INTERFACE)

		list(APPEND EXPORT_TARGETS ${INTERFACE_LIB})
	else()
		set(INTERFACE_LIB ${NAME})
	endif()

	set(PUBLIC_HEADER_PREFIX "include")
	if (AW_INCLUDE_PREFIX)
		set(PUBLIC_HEADER_PREFIX "${PUBLIC_HEADER_PREFIX}/${AW_INCLUDE_PREFIX}")
	endif()
	if (AW_SPLIT_INCLUDES)
		set(PUBLIC_HEADER_PREFIX "${PUBLIC_HEADER_PREFIX}/${NAME}")
	endif()

	if (ARG_EXPORT_NAME)
		set_property(TARGET ${NAME} PROPERTY EXPORT_NAME ${ARG_EXPORT_NAME})
	endif()

	if (AW_MAKE_TESTS AND IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/tests")
		add_subdirectory(tests)
	endif()

	if (IS_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/include")
		target_include_directories(${INTERFACE_LIB}
			${INCLUDE_TYPE}
				$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
				$<INSTALL_INTERFACE:${PUBLIC_HEADER_PREFIX}>)
		install(
			DIRECTORY
				${CMAKE_CURRENT_SOURCE_DIR}/include/
			DESTINATION ${PUBLIC_HEADER_PREFIX}
			COMPONENT
				Devel
		)
	endif()

	install(
		TARGETS
			${EXPORT_TARGETS}
		EXPORT
			${AW_PROJECT_NAME}_targets
		LIBRARY DESTINATION lib
		ARCHIVE DESTINATION lib
		RUNTIME DESTINATION bin
	)
endfunction()


function(aw_add_test NAME)
	set(options NEGATIVE)
	set(arguments)
	set(multivalue SOURCES PARAMS)
	cmake_parse_arguments(PARSE_ARGV 1 ARG "${options}" "${arguments}" "${multivalue}")

	if (AW_OUTPUT_JUNIT)
		set(ADDITIONAL_PARAMS)
	else()
		set(ADDITIONAL_PARAMS "--output-format=junit")
	endif()

	add_executable(${NAME} ${ARG_SOURCES})
	add_test(
		NAME ${NAME}
		COMMAND ${NAME} ${ARG_PARAMS} ${ADDITIONAL_PARAMS}
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})

	if (ARG_NEGATIVE)
		set_property(TEST ${NAME} PROPERTY WILL_FAIL true)
	endif()
endfunction()
