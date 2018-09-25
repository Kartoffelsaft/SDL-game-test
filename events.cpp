#include "game.h"

void keyboardState()
{
  const Uint8* keys{SDL_GetKeyboardState(NULL)};

  using RenderData::camera;

  {
    using namespace Geometry;

    if(keys[SDL_SCANCODE_W])            //camera movement
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

    if(keys[SDL_SCANCODE_UP])           //camera rotation
    {camera.look(ROT_UP * 2);}
    if(keys[SDL_SCANCODE_DOWN])
    {camera.look(ROT_DOWN * 2);}
    if(keys[SDL_SCANCODE_RIGHT])
    {camera.look(ROT_RIGHT * 2);}
    if(keys[SDL_SCANCODE_LEFT])
    {camera.look(ROT_LEFT * 2);}
    if(keys[SDL_SCANCODE_Q])
    {camera.look(ROT_ROLL_LEFT * 2);}
    if(keys[SDL_SCANCODE_E])
    {camera.look(ROT_ROLL_RIGHT * 2);}

    if(keys[SDL_SCANCODE_P])            //reset camera rotation
    {camera.rotation = {0, 0, 0};}
    if(keys[SDL_SCANCODE_O])            //just spins on of the meshes for testing
    {meshes.at(1).rotation += {0, 5, 0};}
  }
}

void events()
{
  SDL_Event event;

  while (SDL_PollEvent(&event))
  {
    switch(event.type)
    {
      case SDL_QUIT:                    //rudiments of dealing with inputs
        beginShutdown();

      break; case SDL_KEYDOWN:
        keyboardState();
    }
  }
  // if(Event.type == SDL_QUIT)
  // {beginShutdown();}


}
