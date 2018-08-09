#include "game.h"

#include <iostream>

int main()
{
  init();

  while(running())
  {
    loop();

    std::cout << "in loop" << std::endl;
  }

  return 0;
}
