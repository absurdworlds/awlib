all: libs

# core
libs: utility io log platform doc graphics obj
io:
	@ $(MAKE) -C 'source/io' $(target)
gui:
	@ $(MAKE) -C 'source/gui' $(target)
graphics:
	@ $(MAKE) -C 'source/graphics' $(target)
obj:
	@ $(MAKE) -C 'source/graphics/meshes' $(target)

doc:
	@ $(MAKE) -C 'source/doc' $(target)

platform:
	@ $(MAKE) -C 'source/platform' $(target)

utility:
	@ $(MAKE) -C 'source/utility' $(target)

log:
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
