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

RoadLSystem::RoadLSystem()
{
  /* Symbols:
   *  - - turn left
   *  + - turn right
   *  E - growth control
   */
  addToAlphabet("-+E");
  setAxiom("E");

  generatedRoads = new std::list<Road*>;
}

RoadLSystem::~RoadLSystem()
{
  freeGeneratedRoads();
}

void RoadLSystem::freeGeneratedRoads()
{
  for(std::list<Road*>::iterator position = generatedRoads->begin();
      position != generatedRoads->end();
      position++)
  {
    delete *position;
  }

  delete generatedRoads;
}

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

Road* RoadLSystem::getNextIdealRoadSegment()
{
  while (generatedRoads->empty())
  /* Keep generating until a road comes up */
  {
    readNextSymbol();
  }

  Road* road = generatedRoads->front();
  generatedRoads->erase(generatedRoads->begin());
  return road;
}

void RoadLSystem::turnLeft()
{
  Vector direction = cursor.getDirection();
  direction.rotateAroundZ((-1) * getTurningAngle());

  cursor.setDirection(direction);
}

void RoadLSystem::turnRight()
{
  cursor.turn(getTurningAngle());
}

void RoadLSystem::drawLine()
{
  Point previousPosition = cursor.getPosition();
  cursor.move(getRoadSegmentLength());
  Point currentPosition = cursor.getPosition();

  generatedRoads->push_back(new Road(Line(previousPosition, currentPosition)));
}
