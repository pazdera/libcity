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
#include "../random.h"
#include "../geometry/vector.h"
#include "../geometry/point.h"
#include "../geometry/linesegment.h"
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

  generatedType = Road::PRIMARY_ROAD;
  minRoadLength = 0;
  maxRoadLength = 0;
  minTurnAngle  = 0;
  maxTurnAngle  = 0;
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

void RoadLSystem::generate()
{
  while (readNextSymbol() != 0)
  {}
}

bool RoadLSystem::generateRoads(int number)
{
  double targetNumberOfRoads = generatedRoads + number;
  bool returnValue = true;
  while (generatedRoads < targetNumberOfRoads && (returnValue = readNextSymbol()) != 0)
  {}

  return returnValue;
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
  Path proposedPath = Path(LineSegment(previousPosition, currentPosition));

  if(!isPathInsideAreaConstraints(&proposedPath))
  /* Path is outside the area constraints */
  {
    cancelBranch();
    return;
  }

  /* Modify path according to localConstraints of existing streets. */
  if (!localConstraints(&proposedPath))
  {
    cancelBranch();
    return;
  }

  if (targetStreetGraph->isIntersectionAtPosition(proposedPath.end()))
  {
    // Don't branch into existing intersections
    cancelBranch();
  }

  /* Add path to the streetgraph */
  cursor.setPosition(proposedPath.end()); /* Set cursor position at the end of generated road. */
  targetStreetGraph->addRoad(proposedPath, generatedType);
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
  Intersection* nearestIntersection = 0;
  double distanceToNearestIntersection = snapDistance + 1;

  Road* nearestRoad = 0;
  double distanceToNearestRoad = snapDistance + 1;
  bool isClose = false;
  bool snapped = false;

  const double MINIMAL_ROAD_LENGTH = 100;

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
    if (distance < snapDistance && distance < distanceToNearestIntersection)
    {
      if (targetStreetGraph->getIntersectionAtPosition((*currentRoad)->end()->position())->numberOfWays() < 4)
      {
      nearestIntersection = (*currentRoad)->begining();
      }
    }

    distance = Vector(proposedPath->end(), (*currentRoad)->end()->position()).length();
    if (distance < snapDistance && distance < distanceToNearestIntersection)
    {
      isClose = true;
      if (targetStreetGraph->getIntersectionAtPosition((*currentRoad)->end()->position())->numberOfWays() < 4)
      {
        nearestIntersection = (*currentRoad)->end();
      }
    }

    Point nearestPointOfRoad = (*currentRoad)->path()->nearestPoint(proposedPath->end());
    distance = Vector(proposedPath->end(), nearestPointOfRoad).length();
    if (distance < snapDistance && distance < distanceToNearestRoad)
    {
      isClose = true;
      if (Vector((*currentRoad)->path()->begining(), nearestPointOfRoad).length() >= MINIMAL_ROAD_LENGTH &&
          Vector((*currentRoad)->path()->end(), nearestPointOfRoad).length() >= MINIMAL_ROAD_LENGTH)
      {
        nearestRoad = (*currentRoad);
      }
    }

    // Measure similarity of the two paths
    // proposedPath is too close to some existing path
    if (proposedPath->distance((*currentRoad)->end()->position()) < snapDistance &&
        proposedPath->distance((*currentRoad)->begining()->position()) < snapDistance)
    {
      return false;
    }

    // Some existing road is too close
    if ((*currentRoad)->path()->distance(proposedPath->begining()) < snapDistance &&
        (*currentRoad)->path()->distance(proposedPath->end()) < snapDistance)
    {
      return false;
    }
  }

  if (nearestIntersection != 0)
  {
    snapped = true;
    proposedPath->setEnd(nearestIntersection->position());
  }
  else
  {
    if (nearestRoad != 0)
    {
      snapped = true;
      proposedPath->setEnd(nearestRoad->path()->nearestPoint(proposedPath->end()));
    }
  }

  if (isClose && !snapped)
  {
    return false;
  }

  if (proposedPath->length() < MINIMAL_ROAD_LENGTH)
  {
    return false;
  }

  if (targetStreetGraph->isIntersectionAtPosition(proposedPath->end()) &&
      targetStreetGraph->getIntersectionAtPosition(proposedPath->end())->numberOfWays() >= 4)
  {
    return false;
  }

//   for (std::list<Road*>::iterator currentRoad = targetStreetGraph->begin();
//         currentRoad != targetStreetGraph->end();
//         currentRoad++)
//   {
//     // Check for intersection
//     if (proposedPath->crosses(*(*currentRoad)->path(), &intersection))
//     {
//       if (intersection == proposedPath->begining() ||
//           intersection == proposedPath->end())
//       /* New road is just touching some other one */
//       {
//       }
//       else
//       /* Cut off the end of the path. */
//       {
//         assert(false);
//       }
//     }
//   }

  return true;
}

void RoadLSystem::setTarget(StreetGraph* target)
{
  targetStreetGraph = target;
}

bool RoadLSystem::isPathInsideAreaConstraints(Path* proposedPath)
{
  bool beginingIsInside = areaConstraints->encloses2D(proposedPath->begining()),
       endIsInside = areaConstraints->encloses2D(proposedPath->end());

  if (!beginingIsInside && !endIsInside)
  {
    return false;
  }

  Point intersection;
  LineSegment  edge;
  int vertices = areaConstraints->numberOfVertices();
  bool touching = false;

  for (int number = 0; number < vertices; number++)
  {
    edge.setBegining(areaConstraints->vertex(number));
    edge.setEnd(areaConstraints->vertex((number + 1) % vertices));

    if (edge.hasPoint2D(proposedPath->begining()) || edge.hasPoint2D(proposedPath->end()))
    {
      touching = true;
      continue;
    }

    if (proposedPath->crosses(Path(edge), &intersection))
    {

      if (!areaConstraints->encloses2D(proposedPath->begining()))
      {
        proposedPath->setBegining(intersection);
      }
      else
      {
        proposedPath->setEnd(intersection);
      }
      break;
    }
  }

  if (touching)
  /* Line is touching, but not crossing any borders => it's all out */
  {
    return false;
  }

  return true;
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


void RoadLSystem::setRoadType(Road::Types type)
{
  generatedType = type;
}

void RoadLSystem::setRoadLength(double min, double max)
{
  minRoadLength = min;
  maxRoadLength = max;
}

void RoadLSystem::setTurnAngle(double min, double max)
{
  minTurnAngle = min;
  maxTurnAngle = max;
}

double RoadLSystem::getRoadSegmentLength()
{
  Random random;
  return random.generateDouble(minRoadLength, maxRoadLength);
}

double RoadLSystem::getTurnAngle()
{
  Random random;
  return random.generateDouble(minTurnAngle, maxTurnAngle);
}

void RoadLSystem::setSnapDistance(double distance)
{
  snapDistance = distance;
}