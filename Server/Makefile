APP_NAME = Server

## Platform name.
UNAME := $(shell uname)

## 32 vs 64 bits.
ARCH := $(shell getconf LONG_BIT)

## x86 vs arm.
PROCESSOR_TYPE := $(shell uname -m)

## LINUX
ifeq ($(UNAME), Linux)

## RASPBERRY PI
ifeq ($(PROCESSOR_TYPE), armv7l)
CC = g++-4.9
CC_FLAGS = -std=c++14 -Wall -pedantic
else
## x86 ARCHITECTURE
CC = g++
CC_FLAGS = -std=c++0x -Wall -pedantic
endif
endif

## MAC
ifeq ($(UNAME), Darwin)
CC = clang++
CC_FLAGS = -std=c++11 -Wall
endif

INCLUDE_SRC = -Iinclude/ -I/Users/alexarse/Project/axFrameworks/axServer/include -I/Users/alexarse/Project/axFrameworks/axUtils/include/

OBJDIR = build
SRC_DIR = source
INCLUDE_DIR = include/

CPP_FILES := $(wildcard source/*.cpp)
OBJ_FILES := $(addprefix build/,$(notdir $(CPP_FILES:.cpp=.o)))
LD_FLAGS := /Users/alexarse/Project/axFrameworks/axServer/lib/libaxServer.a /Users/alexarse/Project/axFrameworks/axUtils/lib/libaxUtils.a

all: createDir $(OBJ_FILES)
	$(CC) $(CC_FLAGS) $(INCLUDE_SRC) $(OBJ_FILES) $(LD_FLAGS) -o $(APP_NAME)

createDir:
	@mkdir -p build 

build/%.o: source/%.cpp
	$(CC) $(CC_FLAGS) $(INCLUDE_SRC) -c -o $@ $<

clean: 
	rm -f $(OBJ_FILES)




