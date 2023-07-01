#include <iostream>
#include <cmath>
#include <SDL2/SDL_image.h>

#include "my_libs.h"

int main() {
  SDL_Window* window = init_window();
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  const Uint8* keys = SDL_GetKeyboardState(NULL);

  float speed = 200.0f;
  float frame_idx = 0;
  std::string path = "/Users/toto/projects/frogger/graphics/player/right/";
  std::vector<SDL_Texture*> animation;

  Time time;
  init_time(&time);

  SDL_FRect rect = {600.0f, 400.0f, 50.0f, 50.0f};
  SDL_FPoint direction = {0.0f, 0.0f};

  SDL_Event event;
  bool running = true;
  while (running) {
    compute_dt(&time);

    create_animation(animation, renderer, path);
    run_event(&event, &running, keys, direction, path);
    update_pos(direction, rect, time, speed);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    animate(renderer, animation, &rect, &frame_idx, time);
    destroy_animation(animation);

    SDL_RenderPresent(renderer);

    // Delay to control frame rate
    SDL_Delay(16); // Delay for 16 milliseconds (approximately 60 frames per second)
  }

  shut_down(renderer, window);
  return 0;
}
