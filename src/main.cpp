#include <iostream>
#include <cmath>
#include "my_libs.h"

float get_magnitude(const SDL_FPoint& vector) {
  float magnitude = std::sqrt(static_cast<float>(vector.x * vector.x + vector.y * vector.y));
  return magnitude;
}

SDL_FPoint normalize(const SDL_FPoint& vector) {
  SDL_FPoint normalize_vec;
  float magnitude = get_magnitude(vector);
  if (magnitude != 0.0f) {
    normalize_vec.x = (vector.x / magnitude);
    normalize_vec.y = (vector.y / magnitude);
  }
  return normalize_vec;
}

int main() {
  SDL_Window* window = init_window();
  SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  const Uint8* keys = SDL_GetKeyboardState(NULL);
  float speed = 200.0f;

  Time time;
  init_time(&time);

  SDL_FRect rect = {600.0f, 400.0f, 50.0f, 50.0f};

  SDL_FPoint direction = {10, 5};

  SDL_Event event;
  bool running = true;
  while (running) {
    compute_dt(&time);
    run_event(&event, &running, keys, direction);

    float magnitude = get_magnitude(direction);
    if (magnitude != 0.0f) {
      direction = normalize(direction);
    }

    rect.x += direction.x * speed * time.dt;
    rect.y += direction.y * speed * time.dt;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRectF(renderer, &rect);

    SDL_RenderPresent(renderer);

    // Delay to control frame rate
    SDL_Delay(16); // Delay for 16 milliseconds (approximately 60 frames per second)
  }

  shut_down(renderer, window);
  return 0;
}
