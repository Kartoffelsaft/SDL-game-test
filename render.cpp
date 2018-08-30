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

void renderMesh(Geometry::mesh mesh)
{
  if(SDL_SetRenderDrawColor(renderer, mesh.meshColor.red, mesh.meshColor.green, mesh.meshColor.blue, mesh.meshColor.alpha) != 0)
  {std::cout << SDL_GetError() << std::endl;}

  for(int i{0}; i < mesh.polys.size(); i++)
  {
    if(SDL_RenderDrawLines(renderer, convertToSDLPointArray(mesh.polys.at(i).vertecies), mesh.polys.at(i).vertecies.size() + 1) != 0)
    {std::cout << SDL_GetError() << std::endl;}
  }
}

void renderMeshes()
{
  for(int i{0}; i < Geometry::meshes.size(); i++)
  {
    renderMesh(Geometry::meshes.at(i));
  }
}

void render()
{
  SDL_GetWindowSize(display, &xResolution, &yResolution);

  if(SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF) != 0)
  {std::cout << SDL_GetError() << std::endl;}

  SDL_RenderClear(renderer);

  SDL_Delay(20);

  renderMeshes();

  SDL_RenderPresent(renderer);
}
