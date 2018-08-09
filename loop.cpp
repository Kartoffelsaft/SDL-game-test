#include "game.h"

#include <iostream>

void loop()
{
  events();

  std::cout << "in loop" << std::endl;

  render();
}
