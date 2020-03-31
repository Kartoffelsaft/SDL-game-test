#include "game.h"

#include <SDL2/SDL.h>

#include <vector>

namespace Geometry
{
  class point
  {
  public:       //coords
    float x;    //+x is right
    float y;    //+y is up
    float z;    //+z is foward

    point operator+(point b) const                              //several operator overloads for convenience
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

  const point ORIGIN{0, 0, 0};      //several constants for legibility in other code
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

  class color                       //Just an RGBA value
  {
  public:
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    unsigned char alpha;
  };


  class screenPolyInfo              //stores info on the polygons that will be later rendered to the screen
  {
  public:
    std::vector<SDL_Point> points;  //the list of 2d points on screen for a single poly
    int pointCount;                 //the number of points in the vector above. mostly a legacy value as that used to be an array
    float distance;                 //how far the center of the poly is from the camera
    color polyColor;                //color of polygon
    bool renderable;                //whether the SDL drawlines function should be used on it. set to false in cases such as the poly's actual location being behind you
  };

  class polygon                     //stores a list of pointers to 3d points in space that make up a polygon
  {
  public:
    std::vector<point*> vertecies;  //they're pointers because it is cheaper on memory
  };

  class bone                        //currently unused. for animation rigging in the future
  {
  public:
    point* vertecies;
    point pivot;
    point rotation;
  };

  class mesh                        //stores a lot data about an object such as where it is, it's polys, etc.
  {
  public:
    point location;
    point rotation;
    color meshColor;

    std::vector<point> vertecies;
    std::vector<polygon> polys;
    std::vector<bone> bones;

    mesh()
    {
      location = {0, 0, 0};
      rotation = {0, 0, 0};
      meshColor = {0xFF, 0xFF, 0xFF, 0xFF};
    }
  };

  class camera                      //stores info about a given camera generally only one will be in use, which is currently initialize in RenderData::
  {
  public:
    point location;
    point rotation;  //rotation is a point class because it would end up being 3 values anyway

    void move(point direction);//both of these are defined in geometry.cpp
    void look(point direction);
  };

  extern std::vector<mesh> meshes;//in geometry.cpp. this stores a list of all the objects in the scene for easy access
}
