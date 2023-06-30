#include <iostream>
#include <cmath>
#include <SDL2/SDL_image.h>
#include <vector>
#include <string>
#include <iostream>

#include "my_libs.h"

void animate(SDL_Renderer* renderer,
             std::vector<SDL_Texture*> animation,
             SDL_FRect* rect, float* frameIndex,
             Time& time) {

    SDL_Texture* currentFrame = nullptr;

    *frameIndex += 10 * time.dt;

    if (*frameIndex >= animation.size()) {
      *frameIndex = 0;
    }

    currentFrame = animation[(int)*frameIndex];
    SDL_RenderCopyF(renderer, currentFrame, NULL, rect);
}

int main() {
  SDL_Window* window = init_window();
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  const Uint8* keys = SDL_GetKeyboardState(NULL);
  float speed = 200.0f;
  float frame_idx = 0;

  std::string path = "/Users/toto/projects/frogger/graphics/player/right/";
  std::vector<SDL_Texture*> animation;
  for (int frame = 0; frame < 4; frame++) {
    std::string img_path = path + std::to_string(frame) + ".png";
    SDL_Surface* surface = IMG_Load(img_path.c_str());
    if (!surface) {
      SDL_Log("Failed to load surface: %s", SDL_GetError());
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    animation.push_back(texture);
  }

  Time time;
  init_time(&time);

  SDL_FRect rect = {600.0f, 400.0f, 50.0f, 50.0f};
  SDL_FPoint direction = {0.0f, 0.0f};

  SDL_Event event;
  bool running = true;
  while (running) {
    compute_dt(&time);
    run_event(&event, &running, keys, direction);
    update_pos(direction, rect, time, speed);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    animate(renderer, animation, &rect, &frame_idx, time);

    SDL_RenderPresent(renderer);

    // Delay to control frame rate
    SDL_Delay(16); // Delay for 16 milliseconds (approximately 60 frames per second)
  }

  shut_down(renderer, window);
  return 0;
}
