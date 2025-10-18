# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Wpedantic
LDFLAGS = 

# Source files
SOURCES = utilities.cpp
TEST_SOURCES = unit_tests.cpp

# Object files
OBJECTS = $(SOURCES:.cpp=.o)
TEST_OBJECTS = $(TEST_SOURCES:.cpp=.o)

# Executable
TARGET = unit_tests

# Default target
all: $(TARGET)

# Compile source files
%.o: %.cpp utilities.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Link executable
$(TARGET): $(OBJECTS) $(TEST_OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)
	@echo ""
	@echo "✓ Build successful!"
	@echo "Run './$(TARGET)' to execute tests"
	@echo ""

# Run tests
test: $(TARGET)
	@echo "Running tests..."
	@echo ""
	./$(TARGET)

# Clean build files
clean:
	rm -f $(OBJECTS) $(TEST_OBJECTS) $(TARGET)
	@echo "Cleaned build files"

# Rebuild
rebuild: clean all

# Help
help:
	@echo "Available targets:"
	@echo "  all      - Build the project (default)"
	@echo "  test     - Build and run tests"
	@echo "  clean    - Remove build files"
	@echo "  rebuild  - Clean and build"
	@echo "  help     - Show this help message"

.PHONY: all test clean rebuild help