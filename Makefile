# Generic Makefile
#
# 1. Prerequisites on header files generated
# 2. Out of source tree build
# 3. Source files in folders with Makefile or below

OUT      = a.out
DIR      = ./.build
SRC      = $(shell find . -type f -name "*.cpp")
OBJ      = $(addprefix $(DIR)/,$(SRC:.cpp=.o))
DEP      = $(OBJ:.o=.d)

CXXFLAGS = -std=c++11 -Wall -W -pedantic -g # -O3
CPPFLAGS = -MMD -MP -DNDEBUG -I../boost_1_73_0 -DBOOST_ALL_DYN_LINK
LDFLAGS  = -L../boost_1_73_0/stage/lib
LDLIBS   = -lpthread -lboost_system -lboost_log -lboost_log_setup -lboost_thread -lboost_chrono -lboost_atomic -lboost_date_time -lboost_filesystem -lboost_regex

# build shared library
#OUT       = ../lib/libhello.so
#CXXFLAGS += -fPIC
#LDFLAGS  += -shared

.PHONY : all clean

all : $(OUT)

$(OUT) : $(OBJ)
	$(CXX) $(LDFLAGS) $(LDLIBS) $^ -o $@

$(DIR)/%.o : %.cpp
	mkdir -p $(dir $@)
	$(CXX) -c $(CXXFLAGS) $(CPPFLAGS) $< -o $@

-include $(DEP)

clean :
	rm -fr $(OUT) $(DIR) $(DEP)
