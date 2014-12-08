ifdef HR_C_COMPILER
 CC = $(HR_C_COMPILER)
else
 CC = cc -std=c99
endif

ifdef HR_CXX_COMPILER
 CXX = $(HR_CXX_COMPILER)
else
 CXX = g++ -std=c++11 
endif

InstallDir = ../../lib

CompilerFlags  = -g -D_DEBUG
CompilerFlags += -fPIC
CompilerFlags += -fno-exceptions
CompilerFlags += -fvisibility=hidden

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
	-rm $(SharedLibFullName) $(Objects) *.o
