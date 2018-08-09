#include "game.h"

int main()
{
  init();

  while(running())
  {
    loop();
  }
  shutdown();

  return 0;
}
