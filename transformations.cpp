#include "game.h"

SDL_Point convertToSDLPoint(Geometry::point oldPoint)
{
  SDL_Point newPoint{(int)oldPoint.x, (int)oldPoint.y};
  return newPoint;
}

SDL_Point* convertToSDLPointArray(std::vector<Geometry::point> oldPoints)
{
  std::vector<SDL_Point> newPoints(oldPoints.size() + 1); //everything about the new points is offset by one because the vector corrupts the first element when being turned into an array

  for(int i{0}; i < oldPoints.size(); i++)
  {
    newPoints.at(i + 1) = convertToSDLPoint(oldPoints.at(i));
  }

  return &newPoints[1];
}
