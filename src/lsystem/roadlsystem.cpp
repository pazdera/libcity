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

#include "../debug.h"

RoadLSystem::RoadLSystem()
{
  /* Symbols:
   *  - - turn left
   *  + - turn right
   *  E - growth control
   */
  addToAlphabet("-+E");
  setAxiom("E");

  generatedRoads = new std::list<Path*>;
}

RoadLSystem::~RoadLSystem()
{
  freeGeneratedRoads();
}

void RoadLSystem::freeGeneratedRoads()
{
  for(std::list<Path*>::iterator position = generatedRoads->begin();
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

Path RoadLSystem::getNextIdealRoadSegment()
{
  while (generatedRoads->empty())
  /* Keep generating until a road comes up */
  {
    readNextSymbol();
  }

  Path roadPath(*generatedRoads->front());

  delete generatedRoads->front();
  generatedRoads->erase(generatedRoads->begin());

  return roadPath;
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

  generatedRoads->push_back(new Path(previousPosition, currentPosition));
}
