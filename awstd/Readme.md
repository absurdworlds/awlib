# awstd library

This library contains fallback implementations for C++ standard library classes and functions.
I do not strive for 100% compliance, implementing only what is needed. Some bits may be missing
(e.g. overloads which I consider redundant), and some non-standard extensions also may be present
(e.g. string\_view constructor from (const char(&)[N])).

This library is written to be used where newer compilers/libraries are not available or I am not allowed to use them.

# awlib

This library also contains parts of awlib ported to C++98.

It also uses awlib's `<aw/config.h>` for platform detection: when awstd is built
inside the awlib tree it is picked up automatically, otherwise point
`AWSTD_AWLIB_INCLUDE_DIR` at the directory containing it, or install awlib and
let `find_package(awlib)` do the job.

# Building

awstd is not built as a part of awlib by default: the rest of awlib is built as
C++23, which is exactly what these fallbacks are not for. It is built separately:

	cmake -S awstd -B build/awstd
	cmake --build build/awstd
	ctest --test-dir build/awstd

or, when it is more convenient, as a part of an awlib build:

	cmake -S . -B build -DAW_ENABLE_AWSTD=ON

| Option                | Default | Description                             |
| --------------------- | ------- | --------------------------------------- |
| `AWSTD_CXX_STANDARD`  | `98`    | C++ standard to build awstd with        |
| `AWSTD_MAKE_TESTS`    | `ON`    | Build the tests                         |
| `AWSTD_AWLIB_INCLUDE_DIR` | autodetected | Where to look for `<aw/config.h>` |

The `std::filesystem` fallback operations (`file_size`, `exists`, `remove`) are
written in C++14, and are only built when `AWSTD_CXX_STANDARD` is 14 or newer.
MSVC cannot select anything older than C++14, so it is used there instead of 98.

# Using

There are two ways to include the headers.

The `awstd::awstd` target puts `include` on the include path, and the headers
are included under their own names:

	#include <awstd/string_view>
	#include <awstd/filesystem>

	awstd::string_view sv = "...";

The `awstd::shims` target additionally puts `include/awstd` on the include path,
which makes the headers available under the names of the standard ones they
replace:

	#include <string_view>

	awstd::string_view sv = "...";

The latter only makes sense for the standards which lack these headers: from
C++17 onwards `<string_view>` and `<filesystem>` would find the shims instead
of the standard headers, so every other user of them in the program would get
the fallbacks as well.

Tests are built for each of these, so both are known to work.
