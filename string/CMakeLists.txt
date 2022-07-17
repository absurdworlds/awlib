
aw_add_library(awstring SHARED
	GLOB_HEADERS
	SOURCES
		compose.cpp # TODO: remove, superseded by std::format
	EXPORT_NAME
		string
)
target_compile_definitions(awstring PRIVATE AW_MODULE_STRING)
target_link_libraries(awstring
    PUBLIC
        awalgo
        awutils # TODO: move string headers here
        awtypes)

try_compile(AW_HAS_CXX_FORMAT
	"${CMAKE_BINARY_DIR}/temp"
	"${CMAKE_CURRENT_SOURCE_DIR}/cmake/test_stdlib_has_fmt.c++"
)

if (AW_HAS_CXX_FORMAT)
	set(AW_FORMAT AW_STD_FORMAT)
else()
	find_package(fmt)

	if (TARGET fmt::fmt)
		target_link_libraries(awstring
			PUBLIC
				fmt::fmt
		)
		set(AW_FORMAT AW_FMTLIB_FORMAT)
	else()
		set(AW_FORMAT AW_NO_FORMAT)
	endif()
endif()

target_compile_definitions(awstring
	PUBLIC
		AW_FORMAT=${AW_FORMAT}
)

message(STATUS "AW_FORMAT: ${AW_FORMAT}")
