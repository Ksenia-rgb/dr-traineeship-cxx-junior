.PHONY: all run build tests test clean

BUILD_DIR = out
OBJ_DIR = $(BUILD_DIR)/obj
BIN_DIR = $(BUILD_DIR)/bin
SOURCE_DIR = src
TEST_DIR = tests
CACHEGRIND_FILE = $(BUILD_DIR)/cachegrind.out

CXX = g++
CPPFLAGS = -std=c++17 -Wall -I $(SOURCE_DIR)
CXXFLAGS = -g

sources = $(wildcard $(SOURCE_DIR)/*.cpp)
objects = $(addprefix $(OBJ_DIR)/, $(sources:.cpp=.o))

test_sources = $(wildcard $(TEST_DIR)/*.cpp)
test_objects = $(addprefix $(OBJ_DIR)/, $(test_sources:.cpp=.o))

main_bin = $(BIN_DIR)/main
test_bin = $(BIN_DIR)/tests

all: build tests

run: build
	@echo "[RUN]"
	@./$(main_bin) $(ARGS)

build: $(objects) | $(BIN_DIR)
	@$(CXX) -o $(main_bin) $^
	@echo "[LINK] $@"

tests: $(test_objects) $(objects) | $(BIN_DIR)
	@$(CXX) -o $(test_bin) $(filter-out %/main.o,$^)
	@echo "[LINK] $@"

test: tests
	@echo "[RUN] tests"
	@./$(test_bin)

cachegrind: build | $(BIN_DIR)
	VALGRIND := $(shell command -v valgrind 2>/dev/null)
	ifeq ($(VALGRIND),)
		$(error valgrind not found)
	endif
	@valgrind --tool=cachegrind --cache-sim=yes --cachegrind-out-file=$(CACHEGRIND_FILE) ./$(main_bin) $(ARGS)
	@cg_annotate --show=Dr --auto=no --threshold=1.0 $(BUILD_DIR)/cachegrind.out

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(BIN_DIR)
	rm -f $(BUILD_DIR)/*.out

$(OBJ_DIR)/%.o: %.cpp | $(OBJ_DIR)
	@$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@
	@echo "[BUILD] $<"

$(BUILD_DIR):
	@mkdir -p $@

$(OBJ_DIR): $(BUILD_DIR)
	@mkdir -p $@
	@mkdir -p $(OBJ_DIR)/src
	@mkdir -p $(OBJ_DIR)/tests

$(BIN_DIR): $(BUILD_DIR)
	@mkdir -p $@
