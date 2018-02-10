## awlib ##
AWLIB is a collection of libraries that I wrote for personal use, as a practice.
I try to make them independent of each other (except for utility libraries, all other libs depend on them).

List of libraries that are currently in this collection:

- utility: various helpers
- type: aliases, containers, type traits etc
- math: template-based linear algebra classes and other things
- algorithm: additional algorithms built on top of std::algorithm
- string: string-manipulation-related utilities
- meta: helpers for template metaprogramming
- log: simple logger facility
- io: facilities for unformatted I/O
- platform: abstraction of platform-specific functions
- archive (v3): header-only serialization library
- graphics: [WIP] attempt at making a rendering engine.
	- Most of available rendering libraries come with their own scene graph, resource managers, input managers, windowing, GUI and so on and so forth.
	- I am trying to make a library that does only rendering, easy to integrate, and offers the best possible performance.

