# build dynamic library with -fPIC -shared
CXXFLAGS    =  -fsanitize=address  -std=c++2a -g # -O3 -fPIC # CXXFLAGS for .cpp
CPPFLAGS  = -MMD -MP -I/home/ljh/Downloads/boost_1_86_0 -DBOOST_LOG_DYN_LINK # -DNDEBUG
LDFLAGS   =  -fsanitize=address  -L/home/ljh/Downloads/boost_1_86_0/stage/lib # -shared
LDLIBS    = -lboost_log -lboost_log_setup -lboost_chrono -lboost_filesystem -lboost_thread -lboost_atomic
CC       = $(CXX) # link with CXX for .cpp

# target name is basename of one of the source files
main : $(patsubst %.cpp,%.o,$(wildcard *.cpp)) # .cpp
-include *.d
clean : ; -rm -fr *.o *.d main
.PHONY : clean
