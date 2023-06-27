#include <stdio.h>
#include "include/game.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

int main() {
  Game game;
  bool success = game.initialize();
  if (success) {
    game.run_loop();
  }

  game.shut_down();
  return 0;
}