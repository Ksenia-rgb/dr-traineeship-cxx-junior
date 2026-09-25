.PHONY: all clean run build test

SRC_DIR     := src
BUILD_DIR   := out
TEST_DIR    := tests

CXX = g++
CXXFLAGS = -O0 -Wall -Wextra -Werror -I$(SRC_DIR)

SOURCES = $(wildcard $(SRC_DIR)/*.cpp)
TEST_SOURCES = $(wildcard $(TEST_DIR)/test-*.cpp)
OBJECTS = $(addprefix $(BUILD_DIR)/, $(notdir $(SOURCES:.cpp=.o)))
MAIN_OBJECT = $(BUILD_DIR)/main.o

all: build

build: $(BUILD_DIR)/main

run: build
	./$(BUILD_DIR)/main $(ARGS)

test: build
	@echo "[TESTS]"

$(BUILD_DIR)/main: $(OBJECTS) | dir
	@$(CXX) $(CXXFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp | dir
	@$(CXX) $(CXXFLAGS) -c $< -o $@

dir:
	@mkdir -p $(BUILD_DIR)

clean:
	@rm -rf $(BUILD_DIR)
