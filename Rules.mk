# Copyright (C) 2015  hedede <haddayn@gmail.com>
#
# License LGPLv3 or later:
# GNU Lesser GPL version 3 <http://gnu.org/licenses/lgpl-3.0.html>
# This is free software: you are free to change and redistribute it.
# There is NO WARRANTY, to the extent permitted by law.

# All project makefiles must define:
# ProjectName
# RootPath
# Objects
# Executable


# Global configuration
Version = 0

EXTRAFLAGS=

# Makefile tricks
comma = ,
space :=
space +=

# Per-project settings
ifeq ($(Executable),true)
	InstallDir = $(RootPath)/bin
	OutputName = $(ProjectName)
else
	InstallDir = $(RootPath)/lib
	OutputShortName = lib$(ProjectName).so
	OutputName = $(OutputShortName).$(Version)
	EXTRAFLAGS += -shared 
endif
BuildDir = $(RootPath)/build/$(ProjectName)
Includes = -I$(RootPath)/include
Objects = $(patsubst %.cpp, $(BuildDir)/%.o, $(Sources))
ProjectDefines = $(addprefix -D,$(Defines))
ProjectDependencies = $(addprefix -l,$(Libraries))


# User configuration
include $(RootPath)/Config.mk

ExtraIncludePaths = $(addprefix -I$(RootPath)/,$(CONFIG_INCLUDE_PATHS))
ExtraLibraryPaths = $(addprefix -L$(RootPath)/,$(CONFIG_LIBRARY_PATHS))

# Tool configuration
MKDIR_P = mkdir -p

CXXFLAGS  = -std=c++14
CXXFLAGS += -fPIC
CXXFLAGS += -fno-exceptions
CXXFLAGS += -fvisibility=default
CXXFLAGS += -fdiagnostics-color=auto
CXXFLAGS_DEBUG   = -g -DDEBUG -D_DEBUG
CXXFLAGS_RELEASE = -O3 -DNDEBUG

CCFLAGS  = -std=c11
CPPFLAGS = $(ProjectDefines) $(Includes) $(ExtraIncludePaths)
LDFLAGS  = -Wl,-rpath-link,$(RootPath)/lib,-R,'$$ORIGIN/../lib' -L$(RootPath)/lib
LDFLAGS += $(ExtraLibraryPaths)
LDFLAGS += $(ProjectDependencies)


# Build rules
all: debug

.PHONY:
debug: CXXFLAGS+=$(CXXFLAGS_DEBUG)
debug: Build

.PHONY: release  
release: CXXFLAGS+=$(CXXFLAGS_RELEASE)
release: Build

$(BuildDir)/%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

.PHONY: directories
directories: BuildDir InstallDir

BuildDir:
	$(MKDIR_P) $(BuildDir)

InstallDir:
	$(MKDIR_P) $(InstallDir)

Build: directories $(Objects)
	$(CXX) $(EXTRAFLAGS) -o $(BuildDir)/$(OutputName) \
	$(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS) $(Objects)
	cp $(BuildDir)/$(OutputName) $(InstallDir)/$(OutputName)
ifeq ($(Executable),false)
	ln -sf $(OutputName) $(InstallDir)/$(OutputShortName)
endif

.PHONY : clean
clean:
	-rm $(Objects) $(BuildDir)/$(OutputName)
