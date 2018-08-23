#include "game.h"

SDL_Point convertToSDLPoint(Geometry::point oldPoint)
{
  SDL_Point newPoint{(int)oldPoint.x, (int)oldPoint.y};
  return newPoint;
}

SDL_Point* convertToSDLPointArray(std::vector<Geometry::point> oldPoints)
{
  std::vector<SDL_Point> newPoints(oldPoints.size());

  for(int i{0}; i < oldPoints.size(); i++)
  {
    newPoints.at(i) = convertToSDLPoint(oldPoints.at(i));
  }

  return newPoints.data();
}
