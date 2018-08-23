#include "game.h"

namespace  RenderData
{
  SDL_Window* display{NULL};
  SDL_Renderer* renderer{NULL};
}
using namespace RenderData;

void render()
{
  if(SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF) != 0)
  {std::cout << SDL_GetError() << std::endl;}

  SDL_RenderClear(renderer);

  Geometry::mesh miscobj;
  miscobj.points = {{0, 0, 0}, {60,40, 0}, {80, 80, 0}, {20, 30, 0}};

  if(SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF) != 0)
  {std::cout << SDL_GetError() << std::endl;}

  //SDL_Point points[4] = {{20, 30}, {60, 40}, {80, 80}, {20, 30}};
  //if(SDL_RenderDrawLines(renderer, points, 4) != 0)
  SDL_Point* points = convertToSDLPointArray(miscobj.points);
  // std::cout << "Points:{";
  // for (int i=0; i<4; i++) {
  //   std::cout << "{" << points[i].x << ", " << points[i].y << "}, ";
  // }
  // std::cout << "}";
  if(SDL_RenderDrawLines(renderer, points, miscobj.points.size()) != 0)
  {std::cout << SDL_GetError() << std::endl;}

  SDL_RenderPresent(renderer);
}
