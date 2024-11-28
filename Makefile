# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -std=c++17 -Wall -I./Components/include -I./Physics/include

# Executable name
TARGET = gyroscope

# Directories
SRC_DIR = .
OBJ_DIR = obj

# Source files
SRC_FILES = $(wildcard Components/src/*.cc Physics/src/*.cc ./*.cc)
OBJ_FILES = $(patsubst %.cc, $(OBJ_DIR)/%.o, $(notdir $(SRC_FILES)))

# Create obj directory if it doesn't exist
$(shell mkdir -p $(OBJ_DIR))

# Build the executable
$(TARGET): $(OBJ_FILES)
	$(CXX) $(OBJ_FILES) -o $(TARGET)

# Build object files
$(OBJ_DIR)/%.o: Components/src/%.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: Physics/src/%.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(OBJ_DIR)/%.o: %.cc
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up
.PHONY: clean
clean:
	rm -f $(OBJ_DIR)/*.o $(TARGET)
