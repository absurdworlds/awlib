# awstd library

This library contains fallback implementations for C++ standard library classes and functions.
I do not strive for 100% compliance, implementing only what is needed. Some bits may be missing (e.g. overloads which I consider redundant), and some non-standard extensions also may be present (e.g. string\_view constructor from (const char(&)[N])).

This library is written to be used where newer compilers/libraries are not available or I am not allowed to use them.

# awlib

This library also contains parts of awlib ported to C++98.
