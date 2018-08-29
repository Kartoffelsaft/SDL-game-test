#include "game.h"

namespace  RenderData
{
  SDL_Window* display{NULL};
  SDL_Renderer* renderer{NULL};

  int xResolution{180};
  int yResolution{180};

  Geometry::camera camera{{0, 0, 0}, {0, 0, 0}};
}
using namespace RenderData;

void render()
{
  SDL_GetWindowSize(display, &xResolution, &yResolution);

  if(SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF) != 0)
  {std::cout << SDL_GetError() << std::endl;}

  SDL_RenderClear(renderer);

  Geometry::mesh miscobj;
  miscobj.vertecies = {{-20, 60, 20}, {60, -40, 1}, {80, 80, 1}, {-20, 60, 1}};

  if(SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF) != 0)
  {std::cout << SDL_GetError() << std::endl;}

  SDL_Point* points = convertToSDLPointArray(miscobj.vertecies);
  if(SDL_RenderDrawLines(renderer, points, miscobj.vertecies.size()) != 0)
  {std::cout << SDL_GetError() << std::endl;}

  SDL_Delay(20);

  SDL_RenderPresent(renderer);
}
