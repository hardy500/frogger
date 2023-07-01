#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <iostream>

// ---------------------------------------------------------------------------------

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
SDL_Window* init_window();

// ---------------------------------------------------------------------------------

typedef struct {
  Uint32 current_time;
  Uint32 previous_time;
  float dt;
} Time;

void init_time(Time* time);
void compute_dt(Time* time);

// ---------------------------------------------------------------------------------

void check_kbd_input(const Uint8* keys, SDL_FPoint& point, std::string& path);

void run_event(SDL_Event* event,
               bool* running,
               const Uint8* keys,
               SDL_FPoint& point,
               std::string& path);

void shut_down(SDL_Renderer* renderer, SDL_Window* window);

// ---------------------------------------------------------------------------------

float get_magnitude(const SDL_FPoint& vector);
SDL_FPoint normalize(const SDL_FPoint& vector);
void update_pos(SDL_FPoint& direction, SDL_FRect& rect, Time& time, float speed);

// ---------------------------------------------------------------------------------
//
void animate(SDL_Renderer* renderer,
             std::vector<SDL_Texture*> animation,
             SDL_FRect* rect,
             float* frameIndex,
             Time& time);

void create_animation(std::vector<SDL_Texture*>& animation, SDL_Renderer* renderer, std::string path);
void destroy_animation(std::vector<SDL_Texture*>& animation);