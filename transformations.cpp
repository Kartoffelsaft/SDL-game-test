#include "game.h"

SDL_Point convertToSDLPoint(Geometry::point oldPoint)
{
  SDL_Point newPoint{0, 0};

  using namespace RenderData;
  newPoint.x = (int)(((yResolution + xResolution)/(FIELD_OF_VIEW * 2) * quickATan(oldPoint.x - camera.location.x, oldPoint.z - camera.location.z))+(xResolution/2));
  newPoint.y = (int)(((yResolution + xResolution)/(FIELD_OF_VIEW * 2) * -quickATan(oldPoint.y - camera.location.y, oldPoint.z - camera.location.z))+(yResolution/2));

  return newPoint;
}

SDL_Point* convertToSDLPointArray(std::vector<Geometry::point> oldPoints)
{
  std::vector<SDL_Point> newPoints(oldPoints.size() + 1); //the new points are offset by one because the vector corrupts the first element when being turned into an array

  for(int i{0}; i < oldPoints.size(); i++)
  {
    newPoints.at(i + 1) = convertToSDLPoint(oldPoints.at(i));
  }

  return &newPoints[1];
}
