#include "game.h"

namespace Geometry
{

  void camera::move(point direction)
  {
    this->location += rotate(ORIGIN, direction, this->rotation, "zxy");
  }
  void camera::look(point direction)
  {
    this->rotation.z += -direction.z; //only use shortly before reseting the camera rotation; it's kind of broken.
    this->rotation.x += quickCosine(this->rotation.z) * -direction.x + quickSine(-this->rotation.z) * direction.y;
    this->rotation.y += quickCosine(this->rotation.z) * -direction.y + quickSine(this->rotation.z) * direction.x;

    this->rotation.y = fmodf(this->rotation.y, 360);
    this->rotation.x = fmodf(this->rotation.x, 360);
  }

  std::vector<mesh> meshes;
}
