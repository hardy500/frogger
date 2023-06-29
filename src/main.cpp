#include <iostream>
#include "my_libs.h"


int main() {
  SDL_Window* window = init_window();
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

  Time time;
  init_time(&time);

  SDL_Rect rect = {WINDOW_WIDTH/2, WINDOW_HEIGHT/2, 64, 64};

  SDL_Event event;
  bool running = true;
  while (running) {
    compute_dt(&time);
    run_event(&event, &running);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderPresent(renderer);

    // Delay to control frame rate
    SDL_Delay(16); // Delay for 16 milliseconds (approximately 60 frames per second)
  }

  shut_down(renderer, window);
  return 0;
}
