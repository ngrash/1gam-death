#include "logging.h"

#include <iostream>
#include <SDL2/SDL.h>

void logSDLError(const std::string& msg) {
  std::cerr << "[ERROR] " << msg << " SDL Error: " << SDL_GetError() << std::endl;
}

#ifdef DEBUG
void logDebug(const std::string& msg) {
  std::cout << "[DEBUG] " << msg << std::endl;
}
#endif // DEBUG
