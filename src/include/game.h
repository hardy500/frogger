#pragma once

#include <SDL2/SDL.h>

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720

class Game {
  public:
  Game();
  bool initialize();
  void run_loop();
  void shut_down();

  private:
  // Helper function
  void process_input();
  void update_game();
  void generate_output();

  SDL_Window* window;
  SDL_Renderer* renderer;
  Uint32 ticks_count; // number of ticks since game started
  bool is_running;
};
