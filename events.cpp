#include "game.h"

void keyboardState()
{
  const Uint8* keys{SDL_GetKeyboardState(NULL)};

  using RenderData::camera;

  if(keys[SDL_SCANCODE_W])
  {camera.location.z += 10;}

  if(keys[SDL_SCANCODE_S])
  {camera.location.z -= 10;}

  if(keys[SDL_SCANCODE_A])
  {camera.location.x -= 10;}

  if(keys[SDL_SCANCODE_D])
  {camera.location.x += 10;}
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
