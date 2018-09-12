#include "game.h"

Geometry::point rotate(Geometry::point pivot, Geometry::point oldPoint, Geometry::point rotation, const char order[3])
{
  Geometry::point newPoint{oldPoint - pivot};
  // Geometry::point relativePoint{oldPoint.x - pivot.x, oldPoint.y - pivot.y, oldPoint.z - pivot.z};

  // newPoint.x = relativePoint.x + (relativePoint.x * (quickCosine(rotation.y) + quickCosine(rotation.z))) - (relativePoint.x * (quickSine(rotation.y) + quickSine(rotation.z))) + pivot.x;
  // newPoint.y = relativePoint.y + (relativePoint.y * (quickCosine(rotation.x) + quickCosine(rotation.z))) - (relativePoint.y * (quickSine(rotation.x) + quickSine(rotation.z))) + pivot.y;
  // newPoint.z = relativePoint.z + (relativePoint.z * (quickCosine(rotation.y) + quickCosine(rotation.x))) - (relativePoint.z * (quickSine(rotation.y) + quickSine(rotation.x))) + pivot.z;

  // newPoint.y *= quickCosine(rotation.x) + quickSine(rotation.x);
  // newPoint.z *= -quickSine(rotation.x) + quickCosine(rotation.x);
  //
  // newPoint.x *= quickCosine(rotation.y) + quickSine(rotation.y);
  // newPoint.z *= -quickSine(rotation.y) + quickCosine(rotation.y);
  //
  // newPoint.x *= quickCosine(rotation.z) + quickSine(rotation.z);
  // newPoint.y *= -quickSine(rotation.z) + quickCosine(rotation.z);

  Geometry::point holder{newPoint};

  for(int i{0}; i < 3; i++)
  {
    if(order[i] == 'x')
    {
      newPoint.y = holder.y * quickCosine(rotation.x) + holder.z * -quickSine(rotation.x);
      newPoint.z = holder.y * quickSine(rotation.x) + holder.z * quickCosine(rotation.x);
      holder = newPoint;
    }

    if(order[i] == 'y')
    {
      newPoint.x = holder.x * quickCosine(rotation.y) + holder.z * -quickSine(rotation.y);
      newPoint.z = holder.x * quickSine(rotation.y) + holder.z * quickCosine(rotation.y);
      holder = newPoint;
    }

    if(order[i] == 'z')
    {
      newPoint.x = holder.x * quickCosine(rotation.z) + holder.y * -quickSine(rotation.z);
      newPoint.y = holder.x * quickSine(rotation.z) + holder.y * quickCosine(rotation.z);
      holder = newPoint;
    }
  }

  newPoint += pivot;

  return newPoint;
}

Geometry::point rotateAroundCamera(Geometry::point oldPoint)
{
  Geometry::point newPoint{oldPoint};

  // newPoint = rotate(RenderData::camera.location, newPoint, {0, -RenderData::camera.rotation.y, 0});
  // newPoint = rotate(RenderData::camera.location, newPoint, {-RenderData::camera.rotation.x, 0, 0});
  // newPoint = rotate(RenderData::camera.location, newPoint, {0, 0, -RenderData::camera.rotation.z});
  newPoint = rotate(RenderData::camera.location, newPoint, -RenderData::camera.rotation, "yxz");

  return newPoint;
}

SDL_Point convertToSDLPoint(Geometry::point oldPoint, Geometry::point meshOrigin, Geometry::point meshRotation, bool *renderable)
{
  using namespace RenderData;

  SDL_Point newPoint{0, 0};

  Geometry::point rotationAdjustedPoint{rotate(Geometry::ORIGIN, oldPoint, -meshRotation) + meshOrigin};
  rotationAdjustedPoint = rotateAroundCamera(rotationAdjustedPoint);
  newPoint.x = (((yResolution + xResolution)/(2*FIELD_OF_VIEW) * quickATan(rotationAdjustedPoint.x - camera.location.x, rotationAdjustedPoint.z - camera.location.z))+(xResolution/2));
  newPoint.y = (((yResolution + xResolution)/(2*FIELD_OF_VIEW) * -quickATan(rotationAdjustedPoint.y - camera.location.y, rotationAdjustedPoint.z - camera.location.z))+(yResolution/2));

  if(rotationAdjustedPoint.z - camera.location.z < 0)
  {
    *renderable = false;

    // if(newPoint.x > xResolution/2)
    // {newPoint.x = -xResolution;}
    // if(newPoint.x < xResolution/2)
    // {newPoint.x = 2 * xResolution;}
    //
    // if(newPoint.y > yResolution/2)
    // {newPoint.y = -yResolution;}
    // if(newPoint.y < yResolution/2)
    // {newPoint.y = 2 * yResolution;}
  }

  return newPoint;
}

// SDL_Point* convertToSDLPointArray(std::vector<Geometry::point*> oldPoints, Geometry::point offset, Geometry::point rotation)
// {
//   std::vector<SDL_Point> newPoints(oldPoints.size() + 2); //the new points are offset by one because the vector corrupts the first element when being turned into an array
//
//   for(int i{0}; i < oldPoints.size(); i++)
//   {
//     Geometry::point rotatedPoint{rotate(Geometry::ORIGIN, oldPoints.at(i)[0], -rotation)};
//     newPoints.at(i + 2) = convertToSDLPoint(rotatedPoint + offset);
//
//     if(newPoints.at(i).x < -RenderData::xResolution/1.01 ||
//        newPoints.at(i).x > RenderData::xResolution * 1.99 ||
//        newPoints.at(i).y < -RenderData::yResolution/1.01 ||
//        newPoints.at(i).y > RenderData::yResolution * 1.99)
//     {
//       goto dontRender;
//     }
//   }
//
//   finish:
//     newPoints.at(1) = newPoints.back();
//     return &newPoints[1];
//
//   dontRender:
//     for(int i{0}; i < newPoints.size(); i++)
//     {newPoints.at(i) = {-1, -1};}
//     goto finish;
// }
