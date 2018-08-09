#include "game.h"
#include <bitset>

std::bitset<8> state{0b00000011};
/*
                       b0 = running
                       b1 = if an event has occurred
*/

bool running()
{
  return state.test(0);
}

void beginShutdown()
{
  state.reset(0);
}
