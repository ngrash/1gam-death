CXX=$(CROSS)g++
PKG_CONFIG=$(CROSS)pkg-config
CXX_FLAGS=--std=c++11 -Werror -Wfatal-errors -Wall -Wextra -Wpedantic -Wconversion -Wshadow `$(PKG_CONFIG) --cflags sdl2`
LIBS=`$(PKG_CONFIG) --libs sdl2 SDL2_image SDL2_ttf SDL2_mixer`

BIN=death$(BIN_EXT)
BUILD_DIR=build
ASSETS_DIR=assets

CPP=$(wildcard src/*.cc)
OBJ=$(CPP:%.cc=$(BUILD_DIR)/%.o)
DEP=$(OBJ:%.o=%.d)

ASE=$(wildcard $(ASSETS_DIR)/*.ase)
PNG=$(ASE:%.ase=%.png)

game: $(BIN) $(PNG)

$(BIN): $(OBJ)
	mkdir -p $(@D)
	$(CXX) $^ -o $@ $(CXX_FLAGS) $(LIBS)
-include $(DEP)

$(BUILD_DIR)/%.o: %.cc
	mkdir -p $(@D)
	$(CXX) -MMD -c $< -o $@ $(CXX_FLAGS)

run:
	./$(BIN)

.PHONY: assets
assets: $(PNG)

%.png: %.ase
	aseprite -b $< --sheet $@ >/dev/null

.PHONY: clean
clean:
	-rm $(BIN) $(OBJ) $(DEP) $(PNG)
