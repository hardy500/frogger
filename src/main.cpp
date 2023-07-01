#include <iostream>
#include <cmath>
#include <SDL2/SDL_image.h>
#include <random>
#include <filesystem>

#include "my_libs.h"

int main() {
  SDL_Window* window = init_window();
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  const Uint8* keys = SDL_GetKeyboardState(NULL);

  //std::string path_cars = "/Users/toto/projects/frogger/graphics/cars/green.png";
  std::string path_cars = "/Users/toto/projects/frogger/graphics/cars";
  //path_cars = getRandomCarName(path_cars.c_str());

  SDL_Texture* texture_car = load_car(path_cars.c_str(), renderer);
  SDL_FRect rect_car_dst = {800.0f, 100.0f, 64.0f, 64.0f};

  float speed = 200.0f;
  float frame_idx = 0;
  std::string path = "/Users/toto/projects/frogger/graphics/player/right/";
  std::vector<SDL_Texture*> animation;

  Time time;
  init_time(time);

  SDL_FRect rect = {600.0f, 400.0f, 64.0f, 64.0f};
  SDL_FPoint direction = {0.0f, 0.0f};

  SDL_Event event;
  bool running = true;
  while (running) {
    compute_dt(time);

    create_animation(animation, renderer, path);
    run_event(&event, running, keys, direction, path);
    update_pos(direction, rect, time, speed);

    if (rect_car_dst.x > -100)
      rect_car_dst.x -= 5;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_RenderCopyExF(renderer, texture_car, nullptr, &rect_car_dst, 0, nullptr, SDL_FLIP_HORIZONTAL);
    animate(renderer, animation, &rect, frame_idx, time, direction);
    destroy_animation(animation);

    SDL_RenderPresent(renderer);

    // Delay to control frame rate
    SDL_Delay(16); // Delay for 16 milliseconds (approximately 60 frames per second)
  }
  shut_down(renderer, window);
  return 0;
}
