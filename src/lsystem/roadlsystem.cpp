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
#include "../geometry/polygon.h"
#include "../geometry/units.h"
#include "../streetgraph/road.h"
#include "../streetgraph/intersection.h"
#include "../streetgraph/path.h"
#include "../streetgraph/streetgraph.h"

#include "../debug.h"

RoadLSystem::RoadLSystem()
{
  generatedRoads    = 0;
  targetStreetGraph = 0;
  areaConstraints   = 0;

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

  /* According to global goals */
  Path proposedPath = Path(Line(previousPosition, currentPosition));

  if(!isPathInsideAreaConstraints(proposedPath))
  /* Path is outside the area constraints */
  {
    cancelBranch();
    return;
  }

  proposedPath.trimOverlapingPart(*areaConstraints);

  /* Modify path according to localConstraints of existing streets. */
  if (!localConstraints(&proposedPath))
  {
    cancelBranch();
    return;
  }

  if (targetStreetGraph->isIntersectionAtPosition(proposedPath.end()))
  {
    // Don't branch from existing intersections
    cancelBranch();
  }

  /* Add path to the streetgraph */
  cursor.setPosition(proposedPath.end()); /* Set cursor position at the end of generated road. */
  targetStreetGraph->addRoad(proposedPath);
  generatedRoads++;
}

void RoadLSystem::cancelBranch()
{
  // Remove everything that would be drawn from this position
  SymbolString::iterator position = currentlyInterpretedSymbol;
  SymbolString::iterator removed;
  while (position != producedString->end() && (*position)->getSymbol() != ']') // FIXME check only for ] is not sufficent!
  {
    removed = position;
    position++;
    producedString->erase(removed);
  }
}

bool RoadLSystem::localConstraints(Path* proposedPath)
{
  // FIXME
  Intersection* nearestIntersection = 0;
  double distanceToNearestIntersection = libcity::SNAP_DISTANCE + 1;

  Road* nearestRoad = 0;
  double distanceToNearestRoad = libcity::SNAP_DISTANCE + 1;

  Point intersection;
  double distance;
  for (std::list<Road*>::iterator currentRoad = targetStreetGraph->begin();
        currentRoad != targetStreetGraph->end();
        currentRoad++)
  {
    // Check for intersection
    if (proposedPath->crosses(*(*currentRoad)->path(), &intersection))
    {

      if (intersection == proposedPath->begining() ||
          intersection == proposedPath->end())
      /* New road is just touching some other one */
      {
      }
      else
      /* Cut off the end of the path. */
      {
        proposedPath->setEnd(intersection);
      }
    }

    // Measure distance of ending point of the path
    //   - to intersection and to the whole path
    distance = Vector(proposedPath->end(), (*currentRoad)->begining()->position()).length();
    if (distance < libcity::SNAP_DISTANCE && distance < distanceToNearestIntersection)
    {
      nearestIntersection = (*currentRoad)->begining();
    }

    distance = Vector(proposedPath->end(), (*currentRoad)->end()->position()).length();
    if (distance < libcity::SNAP_DISTANCE && distance < distanceToNearestIntersection)
    {
      nearestIntersection = (*currentRoad)->end();
    }

    distance = Vector(proposedPath->end(), (*currentRoad)->path()->nearestPoint(proposedPath->end())).length();
    if (distance < libcity::SNAP_DISTANCE && distance < distanceToNearestRoad)
    {
      nearestRoad = (*currentRoad);
    }

    // Measure similarity of the two paths
    // proposedPath is too close to some existing path
    if (proposedPath->distance((*currentRoad)->end()->position()) < libcity::SNAP_DISTANCE &&
        proposedPath->distance((*currentRoad)->begining()->position()) < libcity::SNAP_DISTANCE)
    {
      return false;
    }

    // Some existing road is too close
    if ((*currentRoad)->path()->distance(proposedPath->begining()) < libcity::SNAP_DISTANCE &&
        (*currentRoad)->path()->distance(proposedPath->end()) < libcity::SNAP_DISTANCE)
    {
      return false;
    }
  }

  if (nearestIntersection != 0)
  {
    proposedPath->setEnd(nearestIntersection->position());
  }
  else
  {
    if (nearestRoad != 0)
    {
      proposedPath->setEnd(nearestRoad->path()->nearestPoint(proposedPath->end()));
    }
  }

  return true;
}

void RoadLSystem::setTarget(StreetGraph* target)
{
  targetStreetGraph = target;
}

bool RoadLSystem::isPathInsideAreaConstraints(Path const& proposedPath)
{
  bool beginingIsInside = areaConstraints->encloses2D(proposedPath.begining()),
       endIsInside = areaConstraints->encloses2D(proposedPath.end());

  return beginingIsInside || endIsInside;
}

void RoadLSystem::setAreaConstraints(Polygon *polygon)
{
  freeAreaConstraints();
  areaConstraints = polygon;
}

void RoadLSystem::freeAreaConstraints()
{
  if (areaConstraints != 0)
  {
    delete areaConstraints;
  }
}