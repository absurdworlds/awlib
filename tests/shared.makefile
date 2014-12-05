ifdef HR_C_COMPILER
 CC = $(HR_C_COMPILER)
else
 CC = clang -std=c99
endif

ifdef HR_CXX_COMPILER
 CXX = $(HR_CXX_COMPILER)
else
 CXX = clang++ -std=c++11 
endif

CompilerFlags  = -g -D_DEBUG
CompilerFlags += -fPIC
CompilerFlags += -fvisibility=hidden

InstallDir = ../../bin

CPPFLAGS = $(Defines) $(Includes)
CXXFLAGS = $(CompilerFlags)
LDFLAGS = $(Libraries)

tests: $(Objects)
	$(CXX) $(Objects) -o $(ExecutableName) $(CPPFLAGS) $(CXXFLAGS) $(LDFLAGS)
	cp -f $(ExecutableName) ../../bin
all: tests

.PHONY : clean
clean:
	-rm $(ExecutableName) $(Objects)
