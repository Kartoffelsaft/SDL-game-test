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
    content.push_back('\n');

    if(content[0] == 'v')
    {
      newMesh.vertecies.push_back({0, 0, 0});

      int dimension{0};
      std::string newNumber{""};
      for(int i{1}; i < content.size(); i++)
      {
        if(content.at(i) == ' ' || content.at(i) == '\n')
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

      newMesh.vertecies.shrink_to_fit();
    }

    if(content[0] == 'f')
    {
      newMesh.polys.push_back({});

      std::string newNumber{""};

      for(int i{2}; i < content.size(); i++)
      {
        if(content.at(i) == ' ')
        {
          newMesh.polys.back().vertecies.push_back(&newMesh.vertecies.at(std::stoi(newNumber) - 1));
          newNumber = "";
        }
        else if(content.at(i) == '\n')
        {
          newMesh.polys.back().vertecies.push_back(&newMesh.vertecies.at(std::stoi(newNumber) - 1));
          break;
        }
        else
        {newNumber.push_back(content.at(i));}
      }

      newMesh.polys.shrink_to_fit();
    }
  }

  return newMesh;
}
