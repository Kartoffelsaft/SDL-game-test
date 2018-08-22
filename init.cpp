#include "game.h"

void init()
{
  using namespace RenderData;

  if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
  {
    std::cout << SDL_GetError() << std::endl;
    beginShutdown();
  }

  display = SDL_CreateWindow("SDL Game", 20, 20, WIDTH, HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE | SDL_WINDOW_VULKAN);
  renderer = SDL_CreateRenderer(display, -1, SDL_RENDERER_ACCELERATED);

  if
  (
    display == NULL ||
    renderer == NULL
  )
  {
    std::cout << SDL_GetError() << std::endl;
    beginShutdown();
  }
}
