#pragma once

#include <SDL/SDL.h>

namespace RenderData
{
  extern SDL_Surface* Display;

  const int WIDTH{640};
  const int HEIGHT{480};
}

void init();
void events();
void loop();
void render();
void shutdown();

bool running();
void beginShutdown();
