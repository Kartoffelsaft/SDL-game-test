#include "game.h"

#include <iostream>

void init()
{
  RenderData::Display = SDL_SetVideoMode(RenderData::WIDTH, RenderData::HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

  if(RenderData::Display == NULL)
  {
    std::cout << "Display Initialization Failed" << std::endl;
    beginShutdown();
  }
}
