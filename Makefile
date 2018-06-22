CXX=g++
CXX_FLAGS=--std=c++11 -Wfatal-errors -Wall# -Wextra Wpedantic -Wconversion -Wshadow
LIBS=-lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

BIN=death
BUILD_DIR=build

CPP=$(wildcard src/*.cc)
OBJ=$(CPP:%.cc=$(BUILD_DIR)/%.o)
DEP=$(OBJ:%.o=%.d)

$(BIN): $(OBJ)
	mkdir -p $(@D)
	$(CXX) $(CXX_FLAGS) $(LIBS) $^ -o $@
-include $(DEP)

$(BUILD_DIR)/%.o: %.cc
	mkdir -p $(@D)
	$(CXX) $(CXX_FLAGS) -MMD -c $< -o $@

run:
	./$(BIN)

.PHONY: clean
clean:
	-rm $(BIN) $(OBJ) $(DEP)
