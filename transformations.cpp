#include "game.h"

Geometry::point rotate(Geometry::point pivot, Geometry::point oldPoint, Geometry::point rotation)
{
  Geometry::point newPoint{oldPoint.x - pivot.x, oldPoint.y - pivot.y, oldPoint.z - pivot.z};
  // Geometry::point relativePoint{oldPoint.x - pivot.x, oldPoint.y - pivot.y, oldPoint.z - pivot.z};

  // newPoint.x = relativePoint.x + (relativePoint.x * (quickCosine(rotation.y) + quickCosine(rotation.z))) - (relativePoint.x * (quickSine(rotation.y) + quickSine(rotation.z))) + pivot.x;
  // newPoint.y = relativePoint.y + (relativePoint.y * (quickCosine(rotation.x) + quickCosine(rotation.z))) - (relativePoint.y * (quickSine(rotation.x) + quickSine(rotation.z))) + pivot.y;
  // newPoint.z = relativePoint.z + (relativePoint.z * (quickCosine(rotation.y) + quickCosine(rotation.x))) - (relativePoint.z * (quickSine(rotation.y) + quickSine(rotation.x))) + pivot.z;

  newPoint.y *= quickCosine(rotation.x) + quickSine(rotation.x);
  newPoint.z *= -quickSine(rotation.x) + quickCosine(rotation.x);

  newPoint.x *= quickCosine(rotation.y) + quickSine(rotation.y);
  newPoint.z *= -quickSine(rotation.y) + quickCosine(rotation.y);

  newPoint.x *= quickCosine(rotation.z) + quickSine(rotation.z);
  newPoint.y *= -quickSine(rotation.z) + quickCosine(rotation.z);

  newPoint.x += pivot.x;
  newPoint.y += pivot.y;
  newPoint.z += pivot.z;

  return newPoint;
}

SDL_Point convertToSDLPoint(Geometry::point oldPoint)
{
  using namespace RenderData;

  SDL_Point newPoint{0, 0};

  Geometry::point rotationAdjustedPoint{rotate(camera.location, oldPoint, camera.rotation)};
  newPoint.x = (int)(((yResolution + xResolution)/(FIELD_OF_VIEW) * quickATan(rotationAdjustedPoint.x - camera.location.x, rotationAdjustedPoint.z - camera.location.z))+(xResolution/2));
  newPoint.y = (int)(((yResolution + xResolution)/(FIELD_OF_VIEW) * -quickATan(rotationAdjustedPoint.y - camera.location.y, rotationAdjustedPoint.z - camera.location.z))+(yResolution/2));

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
