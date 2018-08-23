#include <vector>

namespace Geometry
{
  class point
  {
  public:
    float x;
    float y;
    float z;
  };

  class triangle
  {
  public:
    point* A;
    point* B;
    point* C;
  };

  class mesh
  {
  public:
    std::vector<point> points;
    std::vector<triangle> tris;
  };
}
