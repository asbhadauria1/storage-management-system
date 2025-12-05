# Makefile for storage_management

MEMCHECK_FLAGS := -fsanitize=address,leak,undefined
CXX ?= g++
NORMAL_CXXFLAGS ?= -std=c++11 -Wall -Wextra -O2
MEMCHECK_CXXFLAGS ?= $(NORMAL_CXXFLAGS) $(MEMCHECK_FLAGS)
DEBUGFLAGS ?= -g -O0
NORMAL_LDFLAGS ?=
MEMCHECK_LDFLAGS ?= $(NORMAL_LDFLAGS) $(MEMCHECK_FLAGS)

SRCS := $(wildcard *.cpp)
BUILD_DIR := build
NORMAL_DIR := $(BUILD_DIR)/normal
MEMCHECK_DIR := $(BUILD_DIR)/memcheck
NORMAL_TARGET := storage_management
MEMCHECK_TARGET := storage_management_memcheck
NORMAL_OBJS := $(patsubst %.cpp,$(NORMAL_DIR)/%.o,$(SRCS))
MEMCHECK_OBJS := $(patsubst %.cpp,$(MEMCHECK_DIR)/%.o,$(SRCS))

.PHONY: all clean run_normal run_memcheck debug

all: $(NORMAL_TARGET) $(MEMCHECK_TARGET)

$(NORMAL_TARGET): $(NORMAL_OBJS)
	$(CXX) $(NORMAL_CXXFLAGS) $(NORMAL_LDFLAGS) -o $@ $^

$(NORMAL_DIR)/%.o: %.cpp
	@mkdir -p $(NORMAL_DIR)
	$(CXX) $(NORMAL_CXXFLAGS) -c $< -o $@

$(MEMCHECK_TARGET): $(MEMCHECK_OBJS)
	$(CXX) $(MEMCHECK_CXXFLAGS) $(MEMCHECK_LDFLAGS) -o $@ $^

$(MEMCHECK_DIR)/%.o: %.cpp
	@mkdir -p $(MEMCHECK_DIR)
	$(CXX) $(MEMCHECK_CXXFLAGS) -c $< -o $@

debug: CXXFLAGS += $(DEBUGFLAGS)
debug: clean $(NORMAL_TARGET)

run_normal: all
	./$(NORMAL_TARGET)

run_memcheck: all
	./$(MEMCHECK_TARGET)

clean:
	rm -rf $(BUILD_DIR)
	rm -f $(NORMAL_TARGET) $(MEMCHECK_TARGET)