CXX=clang++
CXXFLAGS=-std=c++98
AWLIB_PATH=/home/awdev/awlib
INCPATH=-I../../include/awstd -I../../include -I$(AWLIB_PATH)/include

.c++:

%.o: %.c++
	$(CXX) $(CXXFLAGS) $(INCPATH) -c $< -o $@

awstd: fspath.o
	$(CXX) fspath.o
