#include "game.h"

SDL_Point convertToSDLPoint(Geometry::point oldPoint)
{
  SDL_Point newPoint{0, 0};

  newPoint.x = 2 * ((int)quickATan(oldPoint.x - RenderData::camera.location.x, oldPoint.z - RenderData::camera.location.z)+45);
  newPoint.y = 2 * ((int)quickATan(oldPoint.y - RenderData::camera.location.y, oldPoint.z - RenderData::camera.location.z)+45);

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
