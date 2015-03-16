InstallDir = ../../lib

CompilerFlags  = -g -D_DEBUG -std=c++14
CompilerFlags += -fPIC
CompilerFlags += -fno-exceptions
CompilerFlags += -fvisibility=hidden
CompilerFlags += -fdiagnostics-color=auto

CCFLAGS = -std=c11
CPPFLAGS = $(Defines) $(Includes)
CXXFLAGS = $(CompilerFlags)
LDFLAGS = $(Libraries)

ifndef Executable
shared: $(Objects)
	$(CXX) $(Objects) -shared -o $(SharedLibFullName) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS)
	cp $(SharedLibFullName) $(InstallDir)/$(SharedLibFullName)
	ln -sf $(SharedLibFullName) $(InstallDir)/$(SharedLibName)
all: shared
endif

.PHONY : clean
clean:
	-rm $(SharedLibFullName) $(Objects)
