all: libs

# core
libs: utility core hdf gui physics platform
core:
	@ $(MAKE) -C 'source/core' $(target)

gui:
	@ $(MAKE) -C 'source/gui' $(target)

hdf:
	@ $(MAKE) -C 'source/hdf' $(target)

physics:
	@ $(MAKE) -C 'source/physics-bt' $(target)

platform:
	@ $(MAKE) -C 'source/platform' $(target)

utility:
	@ $(MAKE) -C 'source/utility' $(target)

logger:
	@ $(MAKE) -C 'source/log' $(target)

# tools
hpacker:
	@ $(MAKE) -C 'source/hpacker' $(target)


# tests
all-tests:
	@ $(MAKE) -C 'source/math/tests'      $(target)	
	@ $(MAKE) -C 'source/io/tests'        $(target)	
	@ $(MAKE) -C 'source/utility/tests'   $(target)
	@ $(MAKE) -C 'source/string/tests'    $(target)
	@ $(MAKE) -C 'source/types/tests'     $(target)
	@ $(MAKE) -C 'source/log/tests'       $(target)