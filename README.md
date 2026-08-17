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

### Fuzzing ###

libFuzzer targets, clang only, and worth building with the sanitizers on
-- without them a fuzzer only finds the crashes bad enough to fault on
their own:

```sh
cmake -S . -B build-fuzz -DAW_FUZZERS=ON \
      -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ \
      -DAW_SANITIZERS=address,undefined
cmake --build build-fuzz
ctest --test-dir build-fuzz -R fuzz
```

A target lives in `<module>/fuzz/`, next to that module's `tests/`, and
is picked up the same way. Each one has a `corpus/` directory, which
serves two purposes: it seeds a real fuzzing run, and ctest replays it as
an ordinary test. That replay is what turns a crash found once into a
regression -- the input goes into `corpus/` and stays there.

ctest only replays; it does not fuzz, so it stays fast and gives the same
result on every machine. Fuzzing proper is a longer, separate run:

```sh
build-fuzz/bin/fuzz_wav fileformat/sound/fuzz/corpus -max_total_time=300
```

Anything it finds is written to the working directory as a
`crash-*`/`oom-*`/`timeout-*` file. Confirm it reproduces, fix it, then
commit the file into that target's `corpus/`.

### Coverage ###

```sh
cmake -S . -B build-cov -DAW_COVERAGE=ON
cmake --build build-cov --target coverage
```

The `coverage` target discards the previous run's counters, runs the tests
and writes a report to `<build>/coverage`, printing a summary as it goes.
GCC and clang each use their own instrumentation and their own report tool
-- gcov with gcovr, and llvm-cov -- rather than clang being pushed through
gcov emulation, where the data format has to match whichever gcov happens
to be installed. clang reports region and branch coverage as well, and is
the better of the two to read.

Coverage implies `-O0`: the inliner and the branch folder rewrite the very
thing being counted, so a report from an optimised build measures
something other than the source in front of you. Configuring a non-Debug
build type with `AW_COVERAGE=ON` warns for that reason.

`AW_COVERAGE_EXCLUDE` is a list of regexes for paths to leave out, and by
default drops the tests themselves, since what is wanted is how much of
the library they reach.

CI runs this and keeps the report as an artifact. There is deliberately no
threshold to fall under: the branch figure is the one worth reading, and a
number to defend tends to attract tests written for the number.

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
