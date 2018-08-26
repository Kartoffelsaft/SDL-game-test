#include "game.h"

void keyboardState()
{
  const Uint8* keys{SDL_GetKeyboardState(NULL)};

  using RenderData::camera;

  {
    using namespace Geometry;

    if(keys[SDL_SCANCODE_W])
    {camera.move(LOC_FOWARD * 5);}
    if(keys[SDL_SCANCODE_S])
    {camera.move(LOC_BACK * 5);}
    if(keys[SDL_SCANCODE_A])
    {camera.move(LOC_LEFT * 5);}
    if(keys[SDL_SCANCODE_D])
    {camera.move(LOC_RIGHT * 5);}
    if(keys[SDL_SCANCODE_R])
    {camera.move(LOC_UP * 5);}
    if(keys[SDL_SCANCODE_F])
    {camera.move(LOC_DOWN * 5);}
  }

  if(keys[SDL_SCANCODE_UP])
  {camera.rotation.x += 2;}
  if(keys[SDL_SCANCODE_DOWN])
  {camera.rotation.x -= 2;}
  if(keys[SDL_SCANCODE_RIGHT])
  {camera.rotation.y += 2;}
  if(keys[SDL_SCANCODE_LEFT])
  {camera.rotation.y -= 2;}
}

void events()
{
  SDL_Event event;

  while (SDL_PollEvent(&event))
  {
    switch(event.type)
    {
      case SDL_QUIT:
        beginShutdown();

      break; case SDL_KEYDOWN:
        keyboardState();
    }
  }
  // if(Event.type == SDL_QUIT)
  // {beginShutdown();}


}
