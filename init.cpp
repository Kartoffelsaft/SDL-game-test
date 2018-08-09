#include "game.h"

#include <iostream>

void init()
{
  using namespace RenderData;

  if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
  {
    SDL_GetError();
    beginShutdown();
  }

  Display = SDL_CreateWindow("SDL Game", 0, 0, WIDTH, HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_VULKAN);
  renderer = SDL_CreateRenderer(Display, -1, SDL_RENDERER_ACCELERATED);

  if
  (
    Display == NULL ||
    renderer == NULL
  )
  {
    SDL_GetError();
    beginShutdown();
  }
}
