#include "game.h"

void shutdown()
{
  SDL_DestroyRenderer(RenderData::renderer);
  SDL_DestroyWindow(RenderData::Display);

  SDL_Quit();
}
