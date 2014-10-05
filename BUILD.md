Build instructions for hrengin
==============================

Be wary that hrengin is designed to work with the most recent compilers.

### Windows ###

Build files for visual studio temporarily unavailable.

### Linux ###

Edit `sources/*/Makefile` and add paths for dependencies into `ExternalIncludes` variable. Which dependencies are required is mentioned in readme.

After that run `make` in each of `sources` directories.

### Other *nix ###

Instructions are same as for Linux, although you might want to modify makefiles to use compiler installed on your system.
