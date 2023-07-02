# Makefile for subdir

# build shared library with -fPIC, -shared
CXXFLAGS    = -std=c++23 # -g -O3 -fPIC # CXXFLAGS for .cpp
CPPFLAGS  = -MMD -MP  -fexec-charset=GBK  -I../foo   -I/home/ljh/Downloads/boost_1_82_0/ -DBOOST_ALL_DYN_LINK -DBOOST_MP_THROW_ET_EXCEPTIONS
LDFLAGS   = -L$(OBJDIR)/foo -L/home/ljh/Downloads/boost_1_82_0/stage/lib # -shared
LDLIBS    = -lglog -lfoo -lpthread -lboost_system -lboost_log -lboost_log_setup -lboost_thread -lboost_chrono -lboost_atomic -lboost_date_time -lboost_filesystem -lboost_regex
CC       = $(CXX) # link with CXX for .cpp

LDFLAGS  += -Wl,-rpath,'$$ORIGIN/../foo'
LDFLAGS  += -Wl,-rpath,'$$ORIGIN/../lib'
# LDFLAGS += -Wl,-soname,$(soname)

# make # NDEBUG=1
ifdef NDEBUG
CXXFLAGS   += -O3 # .cpp
CPPFLAGS += -DNDEBUG
else
CXXFLAGS   += -g # .cpp
LDFLAGS  += -fsanitize=address
endif

SUBDIR    = $(OBJDIR)/$(lastword $(subst /, ,$(CURDIR)))

all : $(SUBDIR)/main # $(SUBDIR)/foo

# https://make.mad-scientist.net/papers/how-not-to-use-vpath/
$(SUBDIR)/main : $(addprefix $(SUBDIR)/,$(patsubst %.cpp,%.o,$(wildcard *.cpp))) # .cpp
	$(CC) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(SUBDIR)/%.o : %.cpp | $(SUBDIR) # .cpp
	$(CC) $(CXXFLAGS) $(CPPFLAGS) -c -o $@ $<

$(SUBDIR) : ; @ mkdir $@

-include $(SUBDIR)/*.d
clean : ; -rm -fr $(SUBDIR)
.PHONY : all clean
