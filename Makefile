all: libs

# core
libs: utility io string
core:
	@ $(MAKE) -C 'source/core' $(TARGET)

io:
	@ $(MAKE) -C 'source/io' $(TARGET)

gui:
	@ $(MAKE) -C 'source/gui' $(TARGET)

hdf:
	@ $(MAKE) -C 'source/hdf' $(TARGET)

physics:
	@ $(MAKE) -C 'source/physics-bt' $(TARGET)

platform:
	@ $(MAKE) -C 'source/platform' $(TARGET)

utility:
	@ $(MAKE) -C 'source/utility' $(TARGET)

string:
	@ $(MAKE) -C 'source/string' $(TARGET)

# tools
hpacker:
	@ $(MAKE) -C 'source/hpacker' $(TARGET)


# tests
tests: guitest
guitest:
	@ $(MAKE) -C 'tests/guitest' $(TARGET)

arg-parser-test:
	@ $(MAKE) -C 'tests/Arg_parse' $(TARGET)
