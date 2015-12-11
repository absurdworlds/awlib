all: libs

# core
libs: core hdf gui physics platform
core:
	@ $(MAKE) -C 'source/core' $(TARGET)

gui:
	@ $(MAKE) -C 'source/gui' $(TARGET)

hdf:
	@ $(MAKE) -C 'source/hdf' $(TARGET)

physics:
	@ $(MAKE) -C 'source/physics-bt' $(TARGET)

platform:
	@ $(MAKE) -C 'source/platform' $(TARGET)

# tests
tests: guitest
guitest:
	@ $(MAKE) -C 'tests/guitest' $(TARGET)

arg-parser-test:
	@ $(MAKE) -C 'tests/Arg_parse' $(TARGET)
