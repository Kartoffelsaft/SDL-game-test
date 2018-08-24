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

  extern Geometry::camera camera;

  const int WIDTH{180};
  const int HEIGHT{180};
}

void init();
void events();
void loop();
void render();
void shutdown();

bool running();
void beginShutdown();


SDL_Point* convertToSDLPointArray(std::vector<Geometry::point>);


float quickSine(float);
float quickCosine(float);
float quickTangent(float);

float quickATan(float, float);
