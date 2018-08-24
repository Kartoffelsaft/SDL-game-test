#include "game.h"

#include <cmath>
#include "math.h"

const int SINE_RESOLUTION{8000};
static float sineTable[SINE_RESOLUTION]{0};
const float PI{3.14159265};

float quickSine(float x)
{
  if(sineTable[111] == 0) //some random value that shouldn't be 0
  {
    for(int i{0}; i < SINE_RESOLUTION; i++)
    {
      sineTable[i] = std::sin(i * PI/(SINE_RESOLUTION * 2));
    }
  }

  x = fmodf(x, 360);
  while(x < 0)
  {x += 360;}   //setting x to be within 360 range

  if(x <= 90)
  {return sineTable[(int)((SINE_RESOLUTION -1) * x/90)];}   //using recursion to funnel the x variable into the relevant 90` angle
  if(x > 90 && x <= 180)
  {return quickSine(180-x);}
  if(x > 180 && x <= 270)
  {return -quickSine(x-180);}
  if(x > 270 && x <= 360)
  {return -quickSine(360-x);}
}

float quickCosine(float x)
{return quickSine(x+90);}

float quickTangent(float x)
{return quickSine(x)/quickCosine(x);}

float quickATan(float opposite, float adjacent)
{
  // float min{-90};
  // float max{90};
  // float mid{(min + max)/2};
  //
  // float tangent{opposite/adjacent};
  // float aTanCheck{quickTangent(mid)};
  //
  // while (std::abs(max - min) > 0.003)
  // {
  //   if(tangent > aTanCheck)
  //   {
  //     min = mid;
  //   }
  //   if(tangent < aTanCheck)
  //   {
  //     max = mid;
  //   }
  //   mid = (min + max)/2;
  //
  //   aTanCheck = quickTangent(mid);
  // }
  //
  // return mid;

  return atan(opposite/adjacent) * 180/PI;
}
