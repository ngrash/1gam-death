#include <iostream>

#include "game.h"

int main(int, char*[]) {
  Game game;

  if(game.Init()) {
    game.Run();
  }
  else {
    std::cerr << "Failed to initialize. Quitting." << std::endl;
  }

  game.Quit();

  std::cout << "bye" << std::endl;
  return 0;
}
