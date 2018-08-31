#pragma once

#include "geometry.h"

#include <SDL2/SDL.h>
#include <vulkan/vulkan.h>

#include <iostream>
#include <vector>
#include <cmath>
#include "math.h"

namespace RenderData
{
  extern SDL_Window* display;
  extern SDL_Renderer* renderer;

  extern int xResolution;
  extern int yResolution;
  const int FIELD_OF_VIEW{90};

  extern Geometry::camera camera;
}

void init();
void events();
void loop();
void render();
void shutdown();

bool running();
void beginShutdown();

Geometry::mesh generateMesh(const char*, Geometry::point);


SDL_Point* convertToSDLPointArray(std::vector<Geometry::point*>, Geometry::point, Geometry::point);


float quickSine(float);
float quickCosine(float);
float quickTangent(float);

float quickATan(float, float);

Geometry::point rotate(Geometry::point, Geometry::point, Geometry::point, const char order[3] = "xyz");
Geometry::point rotateAroundCamera(Geometry::point);
