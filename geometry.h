#include <vector>

namespace Geometry
{
  class point
  {
  public:
    float x;
    float y;
    float z;

    point operator+(point b)
    {return {this->x + b.x, this->y + b.y, this->z + b.z};}

    point operator-(point b)
    {return {this->x - b.x, this->y - b.y, this->z - b.z};}

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
  };

  class triangle
  {
  public:
    point* A;
    point* B;
    point* C;

    triangle()
    {
      A = 0;
      B = 0;
      C = 0;
    }
    ~triangle()
    {
      delete A;
      delete B;
      delete C;
    }
  };

  class mesh
  {
  public:
    std::vector<point> points;
    std::vector<triangle> tris;
  };

  class camera
  {
  public:
    point location;
    point rotation;  //rotation is a point class because it would end up being 3 values anyway
  };
}
