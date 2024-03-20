
aw_add_library(awstd STATIC
	SPLIT_INTERFACE
	HEADERS
		include/awstd/C++98/nullptr.h
		include/awstd/C++98/bits/fs/path.h
		include/awstd/C++14/bits/fs/ops.h
	SOURCES
		source/C++98/fspath.c++
		source/C++14/posix_fsops.c++
		source/C++14/win32_fsops.c++
	EXPORT_NAME
		std
)
