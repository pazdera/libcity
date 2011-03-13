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
  defineAlphabet();
}

RoadLSystem::~RoadLSystem()
{}

void RoadLSystem::defineAlphabet()
{
  alphabet.insert('D'); //! Draw line of a random length

  alphabet.insert('L'); //! Turn left 90 degrees
  alphabet.insert('R'); //! Turn right 90 degrees
}

void RoadLSystem::interpretSymbol(char symbol)
{
  GraphicLSystem::interpretSymbol(symbol);

  switch (symbol)
  {
    case 'D':
      // draw line
    case 'L':
      turnLeft90Degrees();
      break;
    case 'R':
      turnRight90Degrees();
      break;
    default:
      // nothing
      break;
  }
}

void RoadLSystem::turnLeft90Degrees()
{
  Vector direction = cursor.getDirection();
  direction.rotateAroundZ(-90);

  cursor.setDirection(direction);
}

void RoadLSystem::turnRight90Degrees()
{
  Vector direction = cursor.getDirection();
  direction.rotateAroundZ(90);

  cursor.setDirection(direction);
}
