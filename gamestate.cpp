#include "game.h"
#include <bitset>

std::bitset<8> state{0b0000'0001};

bool running()
{
  return state.test(0);
}

void shutdown()
{
  state.reset(0);
}
