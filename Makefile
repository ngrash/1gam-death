compile: src/*.cc
	g++ $^ -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -Wall -o death

debug: src/*.cc
	g++ $^ -g -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -Wall -o death -D DEBUG

run:
	./death
