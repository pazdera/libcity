/**
 * This code is part of libcity library.
 *
 * @file lsystem/graphiclsystem.cpp
 * @date 12.03.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @see roadlsystem.h
 *
 */

#include "roadlsystem.h"
#include "../geometry/vector.h"

RoadLSystem::RoadLSystem()
{
  /* Symbols:
   *  - - turn left
   *  + - turn right
   *  E - growth control
   */
  addToAlphabet("-+E");
  setAxiom("E");
}

RoadLSystem::~RoadLSystem()
{}

void RoadLSystem::interpretSymbol(char symbol)
{
  GraphicLSystem::interpretSymbol(symbol);

  switch (symbol)
  {
    case '-':
      turnLeft();
      break;
    case '+':
      turnRight();
      break;
    case 'E':
      // nothing just control character
      break;
    default:
      // nothing
      break;
  }
}

