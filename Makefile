# Compiler and flags
CXX := g++
CXXFLAGS := -Wall -std=c++20 -Iinclude
ifeq ($(DEBUG), true)
	CXXFLAGS += -DDEBUG
endif
ifeq ($(ISR), true)
	CXXFLAGS += -DISR
endif
LDFLAGS := 

# Directories
SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := bin
INCLUDE_DIR := include
TEST_DIR := test
TEST_OBJ_DIR := obj/test

# Output binary name
TARGET := $(BIN_DIR)/RVSIM
TEST_TARGET := $(BIN_DIR)/run_tests

# Find all source and header files
SOURCES := $(wildcard $(SRC_DIR)/*.cpp)
HEADERS := $(wildcard $(INCLUDE_DIR)/*.h) $(wildcard $(INCLUDE_DIR)/*.hpp)
OBJECTS := $(patsubst $(SRC_DIR)/%.cpp, $(OBJ_DIR)/%.o, $(SOURCES))

# Unit test source files
TEST_SOURCES := $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJECTS := $(patsubst $(TEST_DIR)/%.cpp, $(TEST_OBJ_DIR)/%.o, $(TEST_SOURCES))

# Default target
build: $(TARGET)

# Link the final binary
$(TARGET): $(OBJECTS) | $(BIN_DIR)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

# Compile source files into object files, ensuring headers trigger recompilation
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp $(HEADERS) | $(OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Build unit tests
test: $(TEST_TARGET)
	@echo "Running tests..."
	@$(TEST_TARGET)

$(TEST_TARGET): $(TEST_OBJECTS) $(filter-out $(OBJ_DIR)/main.o, $(OBJECTS)) | $(BIN_DIR)
	$(CXX) $(TEST_OBJECTS) $(filter-out $(OBJ_DIR)/main.o, $(OBJECTS)) -o $(TEST_TARGET) $(LDFLAGS)

$(TEST_OBJ_DIR)/%.o: $(TEST_DIR)/%.cpp $(HEADERS) | $(TEST_OBJ_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Ensure necessary directories exist
$(BIN_DIR) $(OBJ_DIR) $(TEST_OBJ_DIR):
	mkdir -p $@

# Clean up
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR) $(TEST_OBJ_DIR)

# Phony targets
.PHONY: build clean test
