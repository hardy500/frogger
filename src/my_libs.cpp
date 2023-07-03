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

void init_time(Time& time) {
  time.current_time = SDL_GetTicks();
  time.previous_time = time.current_time;
  time.dt = 0.0f;
}

void compute_dt(Time& time) {
  time.previous_time = time.current_time;
  time.current_time = SDL_GetTicks();
  time.dt = (time.current_time - time.previous_time) / 1000.0f;
  if (time.dt > 0.05f)
    time.dt = 0.05f;
}

//----------------------------------------------------------------------------------


void check_kbd_input(const Uint8* keys, SDL_FPoint& point, std::string& path) {
  std::string og_path = "/Users/toto/projects/frogger/graphics/player";
  if (keys[SDL_SCANCODE_RIGHT]) {
    path = og_path + "/right/";
    point.x = 1;
  } else if (keys[SDL_SCANCODE_LEFT]) {
    path = og_path + "/left/";
    point.x = -1;
  } else {
    point.x = 0;
  }

  if (keys[SDL_SCANCODE_UP]) {
    path = og_path + "/up/";
    point.y = -1;
  } else if (keys[SDL_SCANCODE_DOWN]) {
    path = og_path + "/down/";
    point.y = 1;
  } else {
    point.y = 0;
  }
}

void run_event(SDL_Event* event,
              bool& running,
              const Uint8* keys,
              SDL_FPoint& point,
              std::string& path) {
  while (SDL_PollEvent(event)) {
    if (event->type == SDL_QUIT) {
      running = false;
    }
    check_kbd_input(keys, point, path);
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

void update_pos(SDL_FPoint& direction, SDL_FRect& rect, Time& time, float& speed) {
  direction = normalize(direction);
  rect.x -= direction.x * speed * time.dt;
  rect.y -= direction.y * speed * time.dt;
}

//----------------------------------------------------------------------------------

void animate(SDL_Renderer* renderer,
             std::vector<SDL_Texture*>& animation,
             SDL_FRect* rect,
             float& frame_index,
             Time& time,
             const SDL_FPoint& vector) {

    SDL_Texture* currentFrame = nullptr;

    float magnitude = std::sqrt(static_cast<float>(vector.x * vector.x + vector.y * vector.y));
    if (magnitude != 0) {
      frame_index += 10 * time.dt;
      if (frame_index >= animation.size())
        frame_index = 0;
    } else {
      frame_index = 0;
    }

    currentFrame = animation[(int)frame_index];
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

void destroy_animation(std::vector<SDL_Texture*>& animation) {
  for (auto a : animation) { SDL_DestroyTexture(a); a = nullptr; }
  animation.clear();
}


std::string getRandomCarName(const std::string& directory) {
  namespace fs = std::filesystem;
  std::vector<std::string> imgList;
  for (const auto& entry : fs::directory_iterator(directory)) {
    if (entry.is_regular_file()) {
      imgList.push_back(entry.path().string());
    }
  }

  if (imgList.empty()) {
    std::cerr << "No images found in the directory: " << directory << std::endl;
    return "";
  }

  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<size_t> dist(0, imgList.size() - 1);
  size_t randomIndex = dist(gen);

  return imgList[randomIndex];
}

// NOTE: refactor this?
SDL_Texture* load_car(std::string path, SDL_Renderer* renderer) {
  std::string random_path = getRandomCarName(path.c_str());
  SDL_Texture* texture_cars = IMG_LoadTexture(renderer, random_path.c_str());
  if (!texture_cars) SDL_Log("Failed to load texture: %s ", SDL_GetError());
  return texture_cars;
}

SDL_Texture* load_bg(std:: string path, SDL_Renderer* renderer) {
  SDL_Texture* texture_bg = IMG_LoadTexture(renderer, path.c_str());
  if (!texture_bg) SDL_Log("Failed to load texture: %s ", SDL_GetError());
  return texture_bg;
}