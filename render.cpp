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

bool inPoly(SDL_Point* points, SDL_Point point, int pointCount)
{
  SDL_Point polyCenter{0, 0};
  for(int i{0}; i < pointCount; i++)
  {
    polyCenter.x += points[i].x;
    polyCenter.y += points[i].y;
  }
  polyCenter.x /= pointCount;
  polyCenter.y /= pointCount;

  for(int i{0}; i+1 < pointCount; i++)
  {
    float slope;
    if(points[i].x - points[i+1].x == 0)
    {continue;}
    slope = (points[i].y + points[i+1].y)/(points[i].x + points[i+1].x);

    bool iLeft{false};
    bool centerAbove{false};
    bool pointCheckAbove{false};

    if(points[i].x < points[i+1].x)
    {iLeft = true;}

    if(iLeft)
    {
      if(polyCenter.x > points[i].x && polyCenter.x < points[i+1].x)
      {
        if(polyCenter.y > (polyCenter.x - points[i].x) * slope + points[i].y)
        {centerAbove = true;}
      }
      if(point.x > points[i].x && point.x < points[i+1].x)
      {
        if(point.y > (point.x - points[i].x) * slope + points[i].y)
        {pointCheckAbove = true;}
      }
    }
    else
    {
      if(polyCenter.x > points[i+1].x && polyCenter.x < points[i].x)
      {
        if(polyCenter.y > (polyCenter.x - points[i+1].x) * slope + points[i+1].y)
        {centerAbove = true;}
      }
      if(point.x > points[i+1].x && point.x < points[i].x)
      {
        if(point.y > (point.x - points[i+1].x) * slope + points[i+1].y)
        {pointCheckAbove = true;}
      }
    }

    if(pointCheckAbove != centerAbove)
    {return false;}
  }

  return true;
}

void renderMeshes()
{
  std::vector<Geometry::screenPolyInfo> screenData;

  for(int i{0}; i < Geometry::meshes.size(); i++)
  {

    for(int j{0}; j < Geometry::meshes.at(i).polys.size(); j++)
    {
      int pointCount{Geometry::meshes.at(i).polys.at(j).vertecies.size() + 1};

      SDL_Point points[pointCount];
      Geometry::point pointTotal = {0, 0, 0};
      bool renderable{true};

      for(int k{0}; k < pointCount - 1; k++)
      {
        points[k] = convertToSDLPoint(*Geometry::meshes.at(i).polys.at(j).vertecies.at(k), Geometry::meshes.at(i).location, Geometry::meshes.at(i).rotation, &renderable);
        pointTotal += *Geometry::meshes.at(i).polys.at(j).vertecies.at(k);

        if(points[k].x < -xResolution/1.01 ||
           points[k].x > xResolution * 1.99 ||
           points[k].y < -yResolution/1.01 ||
           points[k].y > yResolution * 1.99)
        {renderable = false;}
      }

      points[pointCount - 1] = points[0];

      pointTotal *= 1/(float)pointCount;
      float avgDistance{quickSquareRoot(pointTotal.x*pointTotal.x + pointTotal.y*pointTotal.y + pointTotal.z*pointTotal.z)};

      screenData.push_back({points, pointCount, avgDistance, Geometry::meshes.at(i).meshColor, renderable});
    }
  }

  for(int i{0}; i < screenData.size(); i++)
  {
    if(screenData.at(i).renderable)
    {
      for(int j{0}; j < screenData.size(); j++)
      {
        if(screenData.at(j).renderable)
        {
          for(int k{0}; k < screenData.at(j).pointCount; k++)
          {
            if(inPoly(screenData.at(i).points, screenData.at(j).points[k], screenData.at(j).pointCount))
            {
              if(screenData.at(i).distance < screenData.at(j).distance)
              {screenData.at(j).renderable = false;}
              if(screenData.at(i).distance > screenData.at(j).distance)
              {screenData.at(i).renderable = false;}
            }
          }
        }
      }
    }
  }

  for(int i{0}; i < screenData.size(); i++)
  {
    if(screenData.at(i).renderable)
    {
      if(SDL_SetRenderDrawColor(renderer, screenData.at(i).polyColor.red, screenData.at(i).polyColor.green, screenData.at(i).polyColor.blue, screenData.at(i).polyColor.alpha) != 0)
      {std::cout << SDL_GetError() << std::endl;}

      if(SDL_RenderDrawLines(renderer, screenData.at(i).points, screenData.at(i).pointCount) != 0)
      {std::cout << SDL_GetError() << std::endl;}
    }
  }
}

void render()
{
  SDL_GetWindowSize(display, &xResolution, &yResolution);

  if(SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF) != 0)
  {std::cout << SDL_GetError() << std::endl;}

  SDL_RenderClear(renderer);

  SDL_Delay(20);

  renderMeshes();

  SDL_RenderPresent(renderer);
}
