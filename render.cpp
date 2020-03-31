#include "game.h"

namespace  RenderData
{
  SDL_Window* display{NULL};
  SDL_Renderer* renderer{NULL};

  int xResolution{180};
  int yResolution{180};

  Geometry::camera camera{{0, 0, 0}, {0, 0, 0}};
}
using namespace RenderData;

bool inPoly(SDL_Point* points, SDL_Point point, int pointCount)     //checks whether a point is inside a polygon
{
  std::vector<int> polyYintercepts(pointCount/2);                   //it basically takes a vertical line that goes through the point,
                                                                    //then looks for intercepts along that line,
                                                                    //then compares those intercepts to the original point

  for(int i{0}; i < pointCount - 1; i++)
  {
    if(point.x == points[i].x)                                      //checking for where the intercepts are
    {polyYintercepts.push_back({points[i].y});}
    else if(point.x == points[i+1].x)
    {polyYintercepts.push_back({points[i+1].y});}

    else if((point.x > points[i].x && point.x < points[i+1].x) ||
       (point.x < points[i].x && point.x > points[i+1].x))
    {
      polyYintercepts.push_back({(points[i].y-points[i+1].y)*((point.x - points[i].x)/(points[i+1].x - points[i].x)) + points[i].y});
    }
  }

  bool segmentInPoly{true};

  for(int i{1}; i < polyYintercepts.size(); i++)                    //comparing the intercepts to the point we're looking for
  {
    if(point.y > polyYintercepts.at(i-1) && point.y < polyYintercepts.at(i))
    {return segmentInPoly;}
    else
    {segmentInPoly ^= true;}
  }

  return false;
}

void renderMeshes()
{
  std::vector<Geometry::screenPolyInfo> screenData;     //a vector to keep all of the on screen polygons in

  for(int i{0}; i < Geometry::meshes.size(); i++)       //making poly info from all the meshes in the scene
  {

    for(int j{0}; j < Geometry::meshes.at(i).polys.size(); j++)
    {
      int pointCount{Geometry::meshes.at(i).polys.at(j).vertecies.size() + 1};  //the +1 is because the first and last element need to be the same to complete the polygon

      std::vector<SDL_Point> points(pointCount);
      Geometry::point pointTotal = {0, 0, 0};       //keeps track of the polygon's location in 3d. avged at the end
      bool renderable{true};                        //a holder for a variable that will later be used to initialize with

      for(int k{0}; k < pointCount - 1; k++)
      {
        points[k] = convertToSDLPoint(*Geometry::meshes.at(i).polys.at(j).vertecies.at(k), Geometry::meshes.at(i).location, Geometry::meshes.at(i).rotation, &renderable);  //places where a point in 3d should be on screen. 
                                                                                                                                                                            //the renderable reference will be set to false if it happens to be behind the camera
        pointTotal += *Geometry::meshes.at(i).polys.at(j).vertecies.at(k);

        if(points[k].x < -xResolution/1.01 ||   //makes the polygon unrenderable if it happens to be way off the screen
           points[k].x > xResolution * 1.99 ||
           points[k].y < -yResolution/1.01 ||
           points[k].y > yResolution * 1.99)
        {renderable = false;}
      }

      points.back() = points[0];    //sets the last element to be the same as the first so that the last side is drawn

      pointTotal *= 1/(float)(pointCount - 1);  //averages the points in the polygon to get it's center
      pointTotal -= camera.location;            //sets the point to be relative to the camera
      float avgDistance{quickSquareRoot(pointTotal.x*pointTotal.x + pointTotal.y*pointTotal.y + pointTotal.z*pointTotal.z)}; //gets the distance to the polygon from the camera using pythagorean theorem

      screenData.push_back({points, pointCount, avgDistance, Geometry::meshes.at(i).meshColor, renderable});    //finally create the polygon in the array
    }
  }

//   for(int i{0}; i < screenData.size(); i++)
//   {
//     if(screenData.at(i).renderable)
//     {
//       for(int j{0}; j < screenData.size(); j++)
//       {
//         if(screenData.at(j).renderable)
//         {
//           for(int k{0}; k < screenData.at(j).pointCount; k++)
//           {
//             if(inPoly(screenData.at(i).points.data(), screenData.at(j).points[k], screenData.at(i).pointCount))             //goes through all of the polygons and looks for situations where they intersect
//             {                                                                                                               //if they do, it assumes the one behind can't be rendered
//               if(screenData.at(i).distance < screenData.at(j).distance)                                                     //commented out for now as it is extremely laggy and doesn't even work
//               {screenData.at(j).renderable = false;}
//               if(screenData.at(i).distance > screenData.at(j).distance)
//               {screenData.at(i).renderable = false;}
// 
//               break;
//             }
//           }
//         }
//       }
//     }
//   }

  for(int i{0}; i < screenData.size(); i++)                                                                                 //attempts to draw all the lines that are marked renderable
  {
    if(screenData.at(i).renderable)
    {
      if(SDL_SetRenderDrawColor(renderer, screenData.at(i).polyColor.red, screenData.at(i).polyColor.green, screenData.at(i).polyColor.blue, screenData.at(i).polyColor.alpha) != 0)
      {std::cout << SDL_GetError() << std::endl;}

      if(SDL_RenderDrawLines(renderer, screenData.at(i).points.data(), screenData.at(i).pointCount) != 0)
      {std::cout << SDL_GetError() << std::endl;}
    }
  }
}

void render()
{
  SDL_GetWindowSize(display, &xResolution, &yResolution);

  if(SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF) != 0)//sets the background black
  {std::cout << SDL_GetError() << std::endl;}

  SDL_RenderClear(renderer);

  SDL_Delay(20);//just to not bog down the cpu. more advanced wait system to be used in the future

  renderMeshes();

  SDL_RenderPresent(renderer);//tells SDL that everything it has been told about needs to be rendered
}
