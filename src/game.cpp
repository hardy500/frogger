#include "include/game.h"

/// Constructor
Game::Game():
window(nullptr),
renderer(nullptr),
ticks_count(0),
is_running(true){}

// ------------------------------------------------------------------------------------------------

bool Game::initialize() {
  // Init sdl
  int result = SDL_Init(SDL_INIT_EVERYTHING);
  if (result != 0) {
    SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
    return false;
  }

  // Create sdl window
  window = SDL_CreateWindow(
    "Frogger",
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    WINDOW_WIDTH,
    WINDOW_HEIGHT,
    0
  );
  if (!window) {
    SDL_Log("Failed to create window: %s", SDL_GetError());
    return false;
  }

  // Create sdl rendere
  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (!renderer) {
    SDL_Log("Failed to create renderer: %s", SDL_GetError());
    return false;
  }

  return true;
}

// ------------------------------------------------------------------------------------------------
//
void Game::run_loop() {
  while (is_running) {
    process_input();
    update_game();
    generate_output();
  }
}

void Game::process_input() {
  SDL_Event event;
  while (SDL_PollEvent(&event)) {
    switch(event.type) {
      case SDL_QUIT:
        is_running = false;
        break;
    }
  }
}

// ------------------------------------------------------------------------------------------------

void Game::update_game() {
  // Wait until 16ms has past since last frame
  while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticks_count + 16));
  float delta_time = (SDL_GetTicks() - ticks_count) / 1000.0f;

  // Clamp max delta time value
  if (delta_time > 0.05f) { delta_time = 0.05f; }
  // update ticks count for next frame
  ticks_count = SDL_GetTicks();
}

// ------------------------------------------------------------------------------------------------

void Game::generate_output() {
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
  SDL_RenderPresent(renderer);
}

// ------------------------------------------------------------------------------------------------

void Game::shut_down() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}