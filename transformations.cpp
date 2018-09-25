#include "game.h"

Geometry::point rotate(Geometry::point pivot, Geometry::point oldPoint, Geometry::point rotation, const char order[3])  //returns a point that is oldPoint rotated by rotation around pivot
{                                                                                                                       //the order[3] is just so that it can be told which axis to rotate around first 
  Geometry::point newPoint{oldPoint - pivot};

  Geometry::point holder{newPoint};

  for(int i{0}; i < 3; i++)//roughly based on vector rotation
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
  newPoint = rotate(RenderData::camera.location, newPoint, -RenderData::camera.rotation, "yxz");//yxz order used because it biases rotation around y more heavily

  return newPoint;
}

SDL_Point convertToSDLPoint(Geometry::point oldPoint, Geometry::point meshOrigin, Geometry::point meshRotation, bool *renderable)   //takes a point in 3d space and tries to place it in the 2d surface
{
  using namespace RenderData;

  SDL_Point newPoint{0, 0};

  Geometry::point rotationAdjustedPoint{rotate(Geometry::ORIGIN, oldPoint, -meshRotation) + meshOrigin};
  rotationAdjustedPoint = rotateAroundCamera(rotationAdjustedPoint);                                        //tries to rotate the point so that it's relativity to 0, 0, 0 is what it was to the camera 
  
  newPoint.x = (((yResolution + xResolution)/(FIELD_OF_VIEW) * quickATan(rotationAdjustedPoint.x - camera.location.x, rotationAdjustedPoint.z - camera.location.z))+(xResolution/2));
  newPoint.y = (((yResolution + xResolution)/(FIELD_OF_VIEW) * -quickATan(rotationAdjustedPoint.y - camera.location.y, rotationAdjustedPoint.z - camera.location.z))+(yResolution/2));

  if(rotationAdjustedPoint.z - camera.location.z < 0)   //if the point is behind the camera, make it unrenderable
  {
    *renderable = false;
  }

  return newPoint;
}
