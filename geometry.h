#include "game.h"

#include <vector>

namespace Geometry
{
  class point
  {
  public:
    float x;
    float y;
    float z;

    point operator+(point b) const
    {return {this->x + b.x, this->y + b.y, this->z + b.z};}

    point operator-(point b) const
    {return {this->x - b.x, this->y - b.y, this->z - b.z};}

    point operator*(float b) const
    {return {this->x * b, this->y * b, this->z * b};}

    point operator*(point b) const //it should be noted that this is NOT vector multiplication, as a*b == b*a
    {return {this->x * b.x, this->y * b.y, this->z * b.z};}

    point operator-() const
    {return{-this->x, -this->y, -this->z};}

    point& operator+=(point b)
    {
      this->x += b.x;
      this->y += b.y;
      this->z += b.z;

      return *this;
    }

    point& operator-=(point b)
    {
      this->x -= b.x;
      this->y -= b.y;
      this->z -= b.z;

      return *this;
    }

    point& operator*=(float b)
    {
      this->x *= b;
      this->y *= b;
      this->z *= b;

      return *this;
    }
  };

  const point ORIGIN{0, 0, 0};
  const point LOC_RIGHT{1, 0, 0};
  const point ROT_RIGHT{0, 1, 0};
  const point LOC_LEFT{-1, 0, 0};
  const point ROT_LEFT{0, -1, 0};
  const point LOC_UP{0, 1, 0};
  const point ROT_UP{1, 0, 0};
  const point LOC_DOWN{0, -1, 0};
  const point ROT_DOWN{-1, 0, 0};
  const point LOC_FOWARD{0, 0, 1};
  const point ROT_ROLL_RIGHT{0, 0, 1};
  const point LOC_BACK{0, 0, -1};
  const point ROT_ROLL_LEFT{0, 0, -1};

  class polygon
  {
  public:
    std::vector<point*> vertecies;
  };

  class bone
  {
  public:
    point* vertecies;
    point pivot;
    point rotation;
  };

  class mesh
  {
  public:
    point location;
    point rotation;

    std::vector<point> vertecies;
    std::vector<polygon> polys;
    std::vector<bone> bones;

    mesh()
    {
      location = {0, 0, 0};
      rotation = {0, 0, 0};
    }
  };

  class camera
  {
  public:
    point location;
    point rotation;  //rotation is a point class because it would end up being 3 values anyway

    void move(point);
    void look(point);
  };

  extern std::vector<mesh> meshes;
}
