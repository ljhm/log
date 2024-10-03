# build dynamic library with -fPIC -shared
CXXFLAGS   = -std=c++2a -g # -O3 -fPIC # CXXFLAGS for .cpp
CPPFLAGS =  -fsanitize=address  -MMD -MP # -DNDEBUG
CPPFLAGS+= -DGLOG_USE_GLOG_EXPORT
CPPFLAGS+= -I/home/ljh/Downloads/glog/src
CPPFLAGS+= -I/home/ljh/Downloads/glog/build
LDFLAGS  =  -fsanitize=address  -L/home/ljh/Downloads/glog/build # -shared
LDLIBS   = -lglog
CC      = $(CXX) # link with CXX for .cpp

# target name is basename of one of the source files
glog : $(patsubst %.cpp,%.o,$(wildcard *.cpp)) # .cpp
-include *.d
clean : ; -rm -fr *.o *.d glog
.PHONY : clean
