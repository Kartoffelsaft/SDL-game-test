#pragma once

#include "geometry.h"

#include <SDL2/SDL.h>
#include <vulkan/vulkan.h>

#include <iostream>
#include <vector>

namespace RenderData
{
  extern SDL_Window* display;
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

SDL_Point* convertToSDLPointArray(std::vector<Geometry::point>);
