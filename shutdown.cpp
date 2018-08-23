#include "game.h"

void shutdown()
{
  SDL_DestroyRenderer(RenderData::renderer);
  SDL_DestroyWindow(RenderData::display);

  SDL_Quit();
}
