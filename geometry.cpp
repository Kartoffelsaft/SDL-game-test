#include "game.h"

namespace Geometry
{
  void camera::move(point direction)
  {
    this->location += rotate(ORIGIN, -direction, this->rotation);
  }
}
