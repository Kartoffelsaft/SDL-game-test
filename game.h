#pragma once

#include <SDL2/SDL.h>

namespace RenderData
{
  extern SDL_Window* Display;
  extern SDL_Renderer* renderer;

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
