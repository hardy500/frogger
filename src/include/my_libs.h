#pragma once
#include <iostream>
#include <cmath>
#include <SDL2/SDL.h>

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

void run_event(SDL_Event* event, bool* running, const Uint8* keys, SDL_FPoint& point);
void shut_down(SDL_Renderer* renderer, SDL_Window* window);

// ---------------------------------------------------------------------------------

float get_magnitude(const SDL_FPoint& vector);
SDL_FPoint normalize(const SDL_FPoint& vector);
void update_pos(SDL_FPoint& direction, SDL_FRect& rect, Time& time, float speed);