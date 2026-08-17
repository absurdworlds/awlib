## awlib ##
AWLIB is a collection of libraries that I wrote for personal use, as a practice.
I try to make them independent of each other (except for utility libraries, all other libs depend on them).

List of libraries that are currently in this collection:

- utility: things that didn't fit anywhere else
- types: aliases, containers, type traits etc
- math: template-based linear algebra classes and other things
- algorithm: additional algorithms built on top of std::algorithm
- string: string-manipulation-related utilities
- meta: helpers for template metaprogramming
- log: simple logger facility
- io: facilities for unformatted I/O
- platform: abstraction of platform-specific functions
- thread: multi-threading primitives
- archive (v3): header-only serialization library
- fileformat/hudf: text-based data interchange format
- fileformat/sound: simple-to-use WAV file reader

And a few work-in-progress libraries:
- assert: debug assertion library, offers extended functionality compared to the standard `<cassert>`.
- graphics: attempt at making a rendering engine.
	- Most of available rendering libraries come with their own scene graph, resource managers, input managers, windowing, GUI and so on and so forth.
	- I am trying to make a library that does only rendering, easy to integrate, and offers the best possible performance.
- lua: C++ bindings for Lua
- fileformat/itd: simple and performant file archive format for games

## Building ##

```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

### Sanitizers ###

`AW_SANITIZERS` takes a list of `address`, `undefined`, `thread`, `memory`
and `leak`. The flags apply to the whole build, so this is a property of the
build directory rather than something to turn on for one target:

```sh
cmake -S . -B build-asan -DAW_SANITIZERS=address,undefined
cmake --build build-asan
ctest --test-dir build-asan --output-on-failure
```

`address`, `thread` and `memory` each need the whole address space and
cannot be combined; asking for two at once is a configure error, as is a
sanitizer whose runtime library is not installed. `leak` is implied by
`address`. MSVC only implements `address`.

`AW_SANITIZER_FAIL_FAST=ON` adds `-fno-sanitize-recover=all`, which turns
a recoverable diagnostic -- UBSan's, mostly -- into an abort, so it fails
the test that produced it rather than printing and carrying on. Off by
default, since printing and carrying on is the more useful behaviour when
working through findings by hand; CI turns it on.

ctest sets `ASAN_OPTIONS` and friends for each test. The suppression files
they point at are in `awlib/cmake/sanitizers/`, and are for leaks and races
inside libraries awlib does not control.

Code that has to know -- there should be very little of it -- can ask
`<aw/config.h>`: `AW_SANITIZER_ADDRESS`, `AW_SANITIZER_THREAD`,
`AW_SANITIZER_MEMORY`, `AW_SANITIZER_UNDEFINED` and `AW_SANITIZER_ANY`.

CI runs asan+ubsan under both gcc and clang, and tsan under clang.

### Static analysis ###

Each analyser is a separate option, off by default, and runs as part of the
compile:

```sh
# clang-tidy, which includes the clang static analyser (clang-analyzer-*).
# Checks are configured in .clang-tidy at the top of the tree.
cmake -S . -B build-tidy -DAW_CLANG_TIDY=ON -DCMAKE_CXX_COMPILER=clang++

# GCC's own analyser.
cmake -S . -B build-analyzer -DAW_GCC_ANALYZER=ON

# cppcheck.
cmake -S . -B build-cppcheck -DAW_CPPCHECK=ON

# include-what-you-use.
cmake -S . -B build-iwyu -DAW_IWYU=ON
```

Add `-DAW_ANALYZER_WERROR=ON` to turn findings into build errors, which is
how CI runs them. `compile_commands.json` is written by default, so the
analysers can equally be run out of band -- `run-clang-tidy -p build`.

Two of these need their expectations set. GCC's analyser is still
experimental for C++: it does not model a libc function filling in the
buffer it is handed, nor the thunk behind a captureless lambda, so those
two checks are off and the rest are left on. cppcheck cannot parse the
macro DSL the tests are written in, so it is scoped to the library sources.

clang-tidy's check list is the one place with a backlog behind it: the
correctness families are on, while a few hundred style and performance
suggestions are switched off individually in `.clang-tidy`, each recorded
with its count. Turning one back on and clearing it is a self-contained
piece of work.
