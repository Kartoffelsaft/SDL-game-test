#include "game.h"

const int SINE_RESOLUTION{8000};
const int ATAN_ITERATIONS{20};
const int ROOT_ITERATIONS{10};
static float sineTable[SINE_RESOLUTION]{0};
const float PI{3.14159265};

float quickSine(float x)        //generates a sine table if it is first being called. future calls reference that sine table
{
  if(sineTable[111] == 0) //chaecking whether a sine teble has been generated (some random value that shouldn't be 0)
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

float quickCosine(float x)  //uses the sine table to generate a cosine
{return quickSine(x+90);}

float quickTangent(float x) //uses a division to generate a tangent
{
  float sine{quickSine(x)};
  float cosine{quickCosine(x)};

  if(cosine == 0)
  {
    return 99999;
  }

  return sine/cosine;
}

float quickATan(float opposite, float adjacent)     //uses guess & check to do inverse tangent
{
  float min{-90};
  float max{90};
  float mid{(min + max)/2};

  if(adjacent == 0)
  {return 90;}

  float tangent{opposite/adjacent};
  float aTanCheck{quickTangent(mid)};

  for (int i{0}; i < ATAN_ITERATIONS; i++)
  {
    if(tangent > aTanCheck)
    {min = mid;}
    if(tangent < aTanCheck)
    {max = mid;}
    if(tangent == aTanCheck)
    {return mid;}

    mid = (min + max)/2;
    // if(mid < 0.003)
    // {return mid;}

    aTanCheck = quickTangent(mid);
  }

  return mid;

  // return atan(opposite/adjacent) * 180/PI;
}

float quickSquareRoot(float x)      //uses guess & check to do square root
{
  float min{0};
  float max{x};
  float mid{(min+max)/2};

  float rootCheck{mid*mid};

  for(int i{0}; i < ROOT_ITERATIONS; i++)
  {
    if(rootCheck > x)
    {max = mid;}
    if(rootCheck < x)
    {min = mid;}
    if(rootCheck == x)
    {return mid;}

    mid = (min + max)/2;
    rootCheck = mid*mid;
  }

  return mid;
}
