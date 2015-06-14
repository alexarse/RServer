APP_NAME = Server

## Platform name.
UNAME := $(shell uname)

## 32 vs 64 bits.
ARCH := $(shell getconf LONG_BIT)

## x86 vs arm.
PROCESSOR_TYPE := $(shell uname -m)

CUDA_CC = nvcc
CUDA_CC_FLAGS = -std=c++11 

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

INCLUDE_SRC = -Iinclude/ -I/Users/CarolineRoss/alex/axServer/include -I/Users/CarolineRoss/alex/axUtils/include/

OBJ_DIR = build
SRC_DIR = source
INC_DIR = include

CPP_FILES := $(wildcard $(SRC_DIR)/*.cpp)
CUDA_FILES := $(wildcard $(SRC_DIR)/*.cu)

# All object file are gonna be in OBJ_DIR folder.
OBJ_FILES := $(addprefix $(OBJ_DIR)/,$(notdir $(CPP_FILES:.cpp=.o)))
CU_OBJ_FILES := $(addprefix $(OBJ_DIR)/,$(notdir $(CUDA_FILES:.cu=.o)))

# CPP_FILES := $(wildcard source/*.cpp)
# OBJ_FILES := $(addprefix build/,$(notdir $(CPP_FILES:.cpp=.o)))
CUDA_LIB = -L/Developer/NVIDIA/CUDA-7.0/lib/ -lcudart
CUDA_INCLUDE = -I/Developer/NVIDIA/CUDA-7.0/include/

LD_FLAGS := /Users/CarolineRoss/alex/axServer/lib/libaxServer.a /Users/CarolineRoss/alex/axUtils/lib/libaxUtils.a

all: createDir $(OBJ_FILES) $(CU_OBJ_FILES)
	$(CC) $(CC_FLAGS) $(INCLUDE_SRC) $(OBJ_FILES) $(CU_OBJ_FILES) $(LD_FLAGS) $(CUDA_LIB) -o $(APP_NAME)

createDir:
	@mkdir -p build 

$(OBJ_DIR)/%.o: source/%.cpp
	$(CC) $(CC_FLAGS) $(INCLUDE_SRC) -c -o $@ $<

$(OBJ_DIR)/%.o: source/%.cu
	$(CUDA_CC) $(CUDA_CC_FLAGS) $(INCLUDE_SRC) $(CUDA_INCLUDE) $(CUDA_LIB) -c -o $@ $<

# build/%.o: source/%.cpp
# 	$(CC) $(CC_FLAGS) $(INCLUDE_SRC) -c -o $@ $<

clean: 
	rm -f $(OBJ_FILES)
	rm -f $(CU_OBJ_FILES)




