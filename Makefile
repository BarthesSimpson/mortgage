CXX ?= g++

# path #
SRC_PATH = src
BUILD_PATH = build
BIN_PATH = $(BUILD_PATH)/bin

# executable # 
BIN_NAME = mortgage

# extensions #
SRC_EXT = cpp

# code lists #
# Find all source files in the source directory, sorted by
# most recently modified
SOURCES = $(shell find $(SRC_PATH) -name '*.$(SRC_EXT)' | sort -k 1nr | cut -f2-)
# Set the object file names, with the source directory stripped
# from the path, and the build path prepended in its place
OBJECTS = $(SOURCES:$(SRC_PATH)/%.$(SRC_EXT)=$(BUILD_PATH)/%.o)
# Set the dependency files that will be used to add header dependencies
DEPS = $(OBJECTS:.o=.d)

# flags #
COMPILE_FLAGS = -std=c++11 -Wall -Wextra -g
INCLUDES = -I include/ -I /usr/local/include
# Space-separated pkg-config libraries used by this project
LIBS =

.PHONY: default_target
default_target: release

.PHONY: release
release: export CXXFLAGS := $(CXXFLAGS) $(COMPILE_FLAGS)
release: dirs
	@$(MAKE) all

.PHONY: dirs
dirs:
	@echo "Creating directories"
	@mkdir -p $(dir $(OBJECTS))
	@mkdir -p $(BIN_PATH)

.PHONY: clean
clean:
	@echo "Deleting $(BIN_NAME) symlink"
	@$(RM) $(BIN_NAME)
	@echo "Deleting directories"
	@$(RM) -r $(BUILD_PATH)
	@$(RM) -r $(BIN_PATH)

# checks the executable and symlinks to the output
.PHONY: all
all: $(BIN_PATH)/$(BIN_NAME)
	@echo "Making symlink: $(BIN_NAME) -> $<"
	@$(RM) $(BIN_NAME)
	@ln -s $(BIN_PATH)/$(BIN_NAME) $(BIN_NAME)

.PHONY: test
test: 
	@echo "Not yet implemented"

# Creation of the executable
$(BIN_PATH)/$(BIN_NAME): $(OBJECTS)
	@echo "Linking: $@"
	$(CXX) $(OBJECTS) -o $@ ${LIBS}

# Add dependency files, if they exist
-include $(DEPS)

# Source file rules
# After the first compilation they will be joined with the rules from the
# dependency files to provide header dependencies
$(BUILD_PATH)/%.o: $(SRC_PATH)/%.$(SRC_EXT)
	@echo "Compiling: $< -> $@"
	$(CXX) $(CXXFLAGS) $(INCLUDES) -MP -MMD -c $< -o $@







# CXX      := -c++
# CXXFLAGS := -pedantic-errors -Wall -Wextra -Werror
# LDFLAGS  := -L/usr/lib -lstdc++ -lm
# BUILD    := ./build
# OBJ_DIR  := $(BUILD)/objects
# APP_DIR  := $(BUILD)/apps
# TARGET   := mortgage
# INCLUDE  := -Iinclude/**
# SRC      := $(wildcard src/*.cpp)


# OBJECTS  := $(SRC:%.cpp=$(OBJ_DIR)/%.o)

# all: build $(APP_DIR)/$(TARGET)

# $(OBJ_DIR)/%.o: %.cpp
# 	@mkdir -p $(@D)
# 	$(CXX) $(CXXFLAGS) $(INCLUDE) -c $< -o $@ $(LDFLAGS)

# $(APP_DIR)/$(TARGET): $(OBJECTS)
# 	@mkdir -p $(@D)
# 	$(CXX) $(CXXFLAGS) -o $(APP_DIR)/$(TARGET) $^ $(LDFLAGS)

# .PHONY: all build clean debug release

# build:
# 	@mkdir -p $(APP_DIR)
# 	@mkdir -p $(OBJ_DIR)

# debug: CXXFLAGS += -DDEBUG -g
# debug: all

# release: CXXFLAGS += -O2
# release: all

# clean:
# 	-@rm -rvf $(OBJ_DIR)/*
# 	-@rm -rvf $(APP_DIR)/*

# test:
# 	@echo "not yet implemented"

# ___________________________

# TARGET_EXEC ?= a.out

# BUILD_DIR ?= ./build
# SRC_DIRS ?= ./src

# SRCS := $(shell find $(SRC_DIRS) -name *.cpp -or -name *.c -or -name *.s -or -name *.hpp)
# OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
# DEPS := $(OBJS:.o=.d)

# INC_FLAGS := -Iinclude

# CPPFLAGS ?= $(INC_FLAGS) -MMD -MP

# $(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
# 	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# # assembly
# $(BUILD_DIR)/%.s.o: %.s
# 	$(MKDIR_P) $(dir $@)
# 	$(AS) $(ASFLAGS) -c $< -o $@

# # c source
# $(BUILD_DIR)/%.c.o: %.c
# 	$(MKDIR_P) $(dir $@)
# 	$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

# # c++ source
# $(BUILD_DIR)/%.cpp.o: %.cpp
# 	$(MKDIR_P) $(dir $@)
# 	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@


# .PHONY: clean

# clean:
# 	$(RM) -r $(BUILD_DIR)

# -include $(DEPS)

# MKDIR_P ?= mkdir -p
