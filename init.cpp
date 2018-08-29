#include "game.h"

void init()
{
  using namespace RenderData;

  if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
  {
    std::cout << SDL_GetError() << std::endl;
    beginShutdown();
  }

  display = SDL_CreateWindow("SDL Game", 20, 20, xResolution, yResolution, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
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

  for(int i{0}; i < SDL_GetNumRenderDrivers(); i++)
  {
    SDL_RendererInfo info{0};
    SDL_GetRendererInfo(renderer, &info);
    std::cout << info.name << std::endl;
  }

  Geometry::meshes.push_back(generateMesh("./objects/testobject.obj", {0, 0, 100}));
}
