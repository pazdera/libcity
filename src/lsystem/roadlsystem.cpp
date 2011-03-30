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
#include "../geometry/point.h"
#include "../geometry/line.h"
#include "../streetgraph/road.h"
#include "../streetgraph/path.h"
#include "../streetgraph/streetgraph.h"

#include "../debug.h"

RoadLSystem::RoadLSystem()
{
  generatedRoads    = 0;
  targetStreetGraph = 0;

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
      /* Try to interpret symbols defined in parent. */
      GraphicLSystem::interpretSymbol(symbol);
      break;
  }
}

void RoadLSystem::generateRoads(int number)
{
  double targetNumberOfRoads = generatedRoads + number;
  while (generatedRoads < targetNumberOfRoads && readNextSymbol() != 0)
  {}
}

void RoadLSystem::turnLeft()
{
  cursor.turn(-1*getTurnAngle());
}

void RoadLSystem::turnRight()
{
  cursor.turn(getTurnAngle());
}

void RoadLSystem::drawLine()
{
  Point previousPosition = cursor.getPosition();
  cursor.move(getRoadSegmentLength());
  Point currentPosition = cursor.getPosition();

  // Add path to the streetgraph
  if (targetStreetGraph->addRoad(Path(Line(previousPosition, currentPosition)), &currentPosition))
  {
    generatedRoads++;
    cursor.setPosition(currentPosition);
  }
  else
  {
    // Remove everything drawn from this position
    SymbolString::iterator position = currentlyInterpretedSymbol;
    SymbolString::iterator removed;
    while (position != producedString->end() && (*position)->getSymbol() != ']')
    {
      removed = position;
      position++;
      producedString->erase(removed);
    }
  }
}

void RoadLSystem::setTarget(StreetGraph* target)
{
  targetStreetGraph = target;
}