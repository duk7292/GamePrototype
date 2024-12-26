# Set the compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Iinclude -Ilib $(shell sdl2-config --cflags) $(shell pkg-config --cflags SDL2_image)

# Linker flags
LDFLAGS = $(shell sdl2-config --libs) $(shell pkg-config --libs SDL2_image)

# Source and build directories
SRC_DIR = src
BUILD_DIR = bin
LIB_DIR = lib

# Find all source files
SRCS = $(shell find $(SRC_DIR) -name '*.cpp')

# Set the object files
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)

# Set the target executable
TARGET = $(BUILD_DIR)/game

# Build rules
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) $(LDFLAGS) -o $(TARGET)

# Compile source files into object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Phony targets
.PHONY: clean

clean:
	rm -rf $(BUILD_DIR)/* $(SRC_DIR)/*~ *~
