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

void check_kbd_input(const Uint8* keys, SDL_FPoint& point) {
  if (keys[SDL_SCANCODE_RIGHT]) {
    point.x = 1;
  } else if (keys[SDL_SCANCODE_LEFT]) {
    point.x = -1;
  } else {
    point.x = 0;
  }

  if (keys[SDL_SCANCODE_UP]) {
    point.y = -1;
  } else if (keys[SDL_SCANCODE_DOWN]) {
    point.y = 1;
  } else {
    point.y = 0;
  }
}

void run_event(SDL_Event* event, bool* running, const Uint8* keys, SDL_FPoint& point) {
  while (SDL_PollEvent(event)) {
    if (event->type == SDL_QUIT) {
      *running = false;
    }
    check_kbd_input(keys, point);
  }
}

//----------------------------------------------------------------------------------

void shut_down(SDL_Renderer* renderer, SDL_Window* window) {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

//----------------------------------------------------------------------------------

SDL_FPoint normalize(const SDL_FPoint& vector) {
  SDL_FPoint normalize_vec;
  float magnitude = std::sqrt(static_cast<float>(vector.x * vector.x + vector.y * vector.y));
  if (magnitude != 0.0f) {
    normalize_vec.x = (vector.x / magnitude);
    normalize_vec.y = (vector.y / magnitude);
  }
  return normalize_vec;
}

void update_pos(SDL_FPoint& direction, SDL_FRect& rect, Time& time, float speed) {
  direction = normalize(direction);
  rect.x += direction.x * speed * time.dt;
  rect.y += direction.y * speed * time.dt;
}

//----------------------------------------------------------------------------------

void animate(SDL_Renderer* renderer,
             std::vector<SDL_Texture*> animation,
             SDL_FRect* rect,
             float* frameIndex,
             Time& time) {

    SDL_Texture* currentFrame = nullptr;

    *frameIndex += 10 * time.dt;

    if (*frameIndex >= animation.size()) {
      *frameIndex = 0;
    }

    currentFrame = animation[(int)*frameIndex];
    SDL_RenderCopyF(renderer, currentFrame, NULL, rect);
}

void create_animation(std::vector<SDL_Texture*>& animation, SDL_Renderer* renderer, std::string path) {
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
}