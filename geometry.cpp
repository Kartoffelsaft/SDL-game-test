#include "game.h"

namespace Geometry
{
  void camera::move(point direction)
  {
    this->location += rotate(ORIGIN, direction, this->rotation, "zxy");
  }
  void camera::look(point direction)
  {
    // this->rotation.y += -direction.y;
    //
    // float sinY{quickSine(this->rotation.y)};
    // float cosY{quickCosine(this->rotation.y)};
    //
    // this->rotation.x += sinY * -direction.y;
    // this->rotation.z += cosY * -direction.y;
    //
    // this->rotation.x += cosY * -direction.x;
    // this->rotation.z += sinY * -direction.x;
    //
    // this->rotation.x += sinY * -direction.z;
    // this->rotation.z += cosY * -direction.z;
    //
    // this->rotation.x = fmodf(this->rotation.x, quickCosine(this->rotation.y));
    // this->rotation.y = fmodf(this->rotation.y, 360);
    // this->rotation.z = fmodf(this->rotation.z, quickSine(this->rotation.y));
    //
    // if(this->rotation.x > cosY)
    // {this->rotation.x = cosY;}
    // if(this->rotation.x < -cosY)
    // {this->rotation.x = -cosY;}
    //
    // if(this->rotation.z > sinY)
    // {this->rotation.z = sinY;}
    // if(this->rotation.z < -sinY)
    // {this->rotation.z = -sinY;}

    this->rotation.z += -direction.z;
    this->rotation.x += quickCosine(this->rotation.z) * -direction.x + quickSine(-this->rotation.z) * direction.y;
    this->rotation.y += quickCosine(this->rotation.z) * -direction.y + quickSine(this->rotation.z) * direction.x;
  }
}
