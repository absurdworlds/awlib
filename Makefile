all: core

core:
	@ $(MAKE) -C 'source/core' $(TARGET)

gui:
	@ $(MAKE) -C 'source/gui' $(TARGET)

tests: guitest

guitest:
	@ $(MAKE) -C 'tests/guitest' $(TARGET)
