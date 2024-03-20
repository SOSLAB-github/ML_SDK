#
#	make file
#

.SUFFIXES : .c .cpp .o 

# 	GNU C++ compiler
CC = gcc
CXX = g++
AR = ar

## current foldername is target name
#TARGET      = $(notdir $(shell pwd)).so
TARGET      = $(notdir $(shell pwd))

BUILD_TIME  = $(shell date +%s)

BUILD_PATH 	= ../libsoslab

BIN_PATH 	= $(BUILD_PATH)/bin
OBJ_PATH 	= $(BUILD_PATH)/obj

SRC_PATH 	= ../example_src/multi_ml

C_SRCS		= $(wildcard $(SRC_PATH)/*.c)
CXX_SRCS	= $(wildcard $(SRC_PATH)/*.cpp)

OBJS 		= $(C_SRCS:$(SRC_PATH)/%.c=$(OBJ_PATH)/%.o)
OBJS 		+= $(CXX_SRCS:$(SRC_PATH)/%.cpp=$(OBJ_PATH)/%.o)

INCS		+= -I../libsoslab/include
INCS		+= -I../libsoslab/include/core
INCS        += -I../libsoslab/include/ml

# libsoslab common options
LIBS        += -L$(BUILD_PATH)/bin

# libsoslab_core options	
LIBS        += -lsoslab_core
LIBS        += -pthread
CXXFLAGS    += -DASIO_STANDALONE 

# libsoslab_ml options
LIBS        += -lsoslab_ml

#	set LDFLAGS and CFLAGS(CXXFLAGS)
LDFLAGS  = $(LIBS) -O2 #-pg

CFLAGS = $(INCS) -c -std=c99 -fPIC 

CXXFLAGS += $(INCS) 
# CXXFLAGS += -c -std=c++11 -fPIC -fopenmp -W -Wfatal-errors -Wall -Wshadow -D__LAST_DEV_BUILD_VER=$(BUILD_TIME) -O2 #-g -pg
CXXFLAGS += -c -std=c++14 -fPIC -fopenmp -W -Wfatal-errors -Wall -Wshadow -D__LAST_DEV_BUILD_VER=$(BUILD_TIME) -O2 #-g -pg

#	rm options
RM 			= @rm -rfv

# 	mkdir options
MKDIR 		= @mkdir -p

$(BIN_PATH)/$(TARGET): $(OBJS)
	$(MKDIR) $(BIN_PATH)
	$(CXX) -o $(BIN_PATH)/$(TARGET) $(OBJS) $(LDFLAGS)
	#$(CXX) -shared -o $(BIN_PATH)/$(TARGET) $(OBJS) $(LDFLAGS)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.cpp
	$(MKDIR) $(OBJ_PATH)
	$(CXX) $(CXXFLAGS) $< -o $@

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	$(MKDIR) $(OBJ_PATH)
	$(CC) $(CFLAGS) $< -o $@

all : $(BIN_PATH)/$(TARGET)

#	clean
# clean:
# 	$(RM) $(BUILD_PATH)/obj
# 	$(RM) $(BUILD_PATH)/bin/$(TARGET)
# 	@echo "Done."

#	include dependency
ifeq (.depend,$(wildcard .depend))
include .depend
endif
