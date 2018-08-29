#include "game.h"

#include <fstream>
#include <string>
#include <stdlib.h>

using namespace Geometry;

mesh generateMesh(const char* objFile, point location)
{
  std::ifstream file;
  std::string content;
  file.open(objFile);

  mesh newMesh;
  newMesh.location = location;

  while(getline(file, content))
  {
    content.push_back(' ');

    if(content[0] == 'v')
    {
      newMesh.vertecies.push_back({0, 0, 0});

      {
        int dimension{0};
        std::string newNumber{""};
        for(int i{1}; i < content.size(); i++)
        {
          if(content.at(i) == ' ')
          {
            if(dimension == 1)
            {newMesh.vertecies.back().x = std::stof(newNumber);}
            if(dimension == 2)
            {newMesh.vertecies.back().y = std::stof(newNumber);}
            if(dimension == 3)
            {newMesh.vertecies.back().z = std::stof(newNumber);}
            if(dimension > 3)
            {break;}

            newNumber = "";
            dimension++;
          }
          else
          {newNumber.push_back(content.at(i));}
        }
      }
    }
  }

  return newMesh;
}
