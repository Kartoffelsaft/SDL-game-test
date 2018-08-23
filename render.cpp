#include "game.h"

namespace  RenderData
{
  SDL_Window* display{NULL};
  SDL_Renderer* renderer{NULL};
}
using namespace RenderData;

void render()
{
  static int startx{0};

  if(SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF) != 0)
  {
    std::cout << SDL_GetError() << std::endl;
  }

  SDL_RenderClear(renderer);

  if(SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF) != 0)
  {
    std::cout << SDL_GetError() << std::endl;
  }
  if(SDL_RenderDrawLine(renderer, startx, 30, 60, 60) != 0)
  {
    std::cout << SDL_GetError() << std::endl;
  }
  startx++;

  SDL_Delay(100);

  SDL_RenderPresent(renderer);
}
