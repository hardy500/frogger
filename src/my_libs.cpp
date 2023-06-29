#include "my_libs.h"

SDL_Window* init_window() {
  SDL_Init(SDL_INIT_VIDEO);

  SDL_Window* window = SDL_CreateWindow(
    "Game Loop",
    SDL_WINDOWPOS_UNDEFINED,
    SDL_WINDOWPOS_UNDEFINED,
    WINDOW_WIDTH, WINDOW_HEIGHT,
    SDL_WINDOW_SHOWN
  );

  if (!window)
    SDL_Log("Failed to init window: %s ", SDL_GetError());
  return window;
}

//----------------------------------------------------------------------------------

void init_time(Time* time) {
  time->current_time = SDL_GetTicks();
  time->previous_time = time->current_time;
  time->dt = 0.0f;
}

void compute_dt(Time* time) {
  time->previous_time = time->current_time;
  time->current_time = SDL_GetTicks();
  time->dt = (time->current_time - time->previous_time) / 1000.0f;
  if (time->dt > 0.05f)
    time->dt = 0.05f;
}

//----------------------------------------------------------------------------------

void run_event(SDL_Event* event, bool* running) {
  while (SDL_PollEvent(event)) {
    if (event->type == SDL_QUIT) {
      *running = false;
    }
  }
}

//----------------------------------------------------------------------------------

void shut_down(SDL_Renderer* renderer, SDL_Window* window) {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}