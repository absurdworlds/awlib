hr engin conventions
====================

## Code conventions

### Braces placement

All the code must adhere to K&R style. Additionally, braces must not be omitted in all scopes.

### Identation style

Tabulation characters should be used for identation. One tab character is equal to eight spaces.

If more then four levels of nesting present, function should be split.

Everything inside a scope must be indented by one level, with exception to labels and namespace scopes.

### Header guards

All header guards should have following format:

`_project_fileName_`

Where `project` refers to a whole product, not to a module or a IDE project file.

## Directory structure

Repository is divided in several folders:
- `source/` contains source code for engine modules;
- `include/` contains headers with API and shared classes and functions;
- `docs/` contains any documentation presented either by plain text or supplemented with a markup language;
- `lib/` contains all compiled (binary) static libraries;
- `bin/` contains any binary executable files and shared libraries;
- `data/` contains any other media such as images, test cases, models, language data etc

### source and include directories

Each module should have it's own directory named `source/{module name}`. Wrapper libraries should have a name `source/{module name}-{external library name}`. Each module also should corresponding directory `include/hrengin/{module name}`. All shared headers not bound to any module should be located in `include/hrengin/common`.

#### hrengin modules

- *game*: everything related to game logic, such as event timer or replay manager
- *core*: modules such as file parsers, model convertors, configuration managers etc
- *graphics*: visuals and gui
- *physics*: physics simulation
- *network*: remote connections
- *audio*: sound
- *platform*: wrappers for platform-specific functions
