#include "game.h"

void init()
{
  using namespace RenderData;

  if(SDL_Init(SDL_INIT_EVERYTHING) != 0)            //stuff for the next few lines is pretty much just SDL stuff
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

  Geometry::meshes.push_back(generateMesh("./objects/testobject.obj", {0, 0, 1000}));       //these two functions basically just spawn in a couple of objects for testing
  Geometry::meshes.push_back(generateMesh("./objects/saxis.obj", {0, 0, 400}));
}
