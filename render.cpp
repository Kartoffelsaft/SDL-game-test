#include "game.h"

namespace  RenderData
{
  SDL_Window* display{NULL};
  SDL_Renderer* renderer{NULL};
}
using namespace RenderData;

void render()
{
  if(SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF) != 0)
  {
    std::cout << SDL_GetError() << std::endl;
  }
  if(SDL_RenderDrawLine(renderer, 30, 30, 60, 60))
  {
    std::cout << SDL_GetError() << std::endl;
  }
}
