#include "game.h"

void events()
{
  SDL_Event Event;
  SDL_PollEvent(&Event);

  if(Event.type == SDL_QUIT)
  {
    beginShutdown();
  }
}
