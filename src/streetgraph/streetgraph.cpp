/**
 * This code is part of libcity library.
 *
 * @file streetgraph.cpp
 * @date 17.02.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @see streetgraph.h
 *
 */

#include "streetgraph.h"
#include "road.h"
#include "intersection.h"
#include "zone.h"
#include "path.h"
#include "areaextractor.h"
#include "../lsystem/roadlsystem.h"
#include "../geometry/polygon.h"
#include "../geometry/linesegment.h"
#include "../geometry/point.h"
#include "../geometry/vector.h"
#include "../geometry/units.h"
#include "../debug.h"

#include <set>
#include <string>
#include <sstream>

StreetGraph::StreetGraph()
{
  initialize();
}

void StreetGraph::initialize()
{
  roads = new std::list<Road*>;
  intersections = new std::list<Intersection*>;
}

StreetGraph::~StreetGraph()
{
  freeMemory();
}

void StreetGraph::freeMemory()
{
  Intersection *removedIntersection = 0;
  Road *removedRoad = 0;

  while (!intersections->empty())
  {
    removedIntersection = intersections->back();
    delete removedIntersection;
    intersections->pop_back();
  }
  delete intersections;

  while (!roads->empty())
  {
    removedRoad = roads->back();
    delete removedRoad;
    roads->pop_back();
  }
  delete roads;
}

std::list<Zone*> StreetGraph::findZones()
{
  debug("StreetGraph::findZones() passing " << intersections->size() << " intersections to MCB.");
  AreaExtractor graph;
  return graph.extractZones(this);
}

Road* StreetGraph::getRoadBetweenIntersections(Intersection* first, Intersection* second)
{
  std::list<Road*> roadsOfFirst = first->getRoads();

  for (std::list<Road*>::iterator road = roadsOfFirst.begin();
       road != roadsOfFirst.end();
       road++)
  {
    if (((*road)->begining() == first && (*road)->end() == second) ||
        ((*road)->begining() == second && (*road)->end() == first))
    {
      return *road;
    }
  }

  return 0;
}


void StreetGraph::addRoad(Path const& path, Road::Types roadType)
{
  Path roadPath(path);

  Point intersection;
  for (StreetGraph::iterator currentRoad = begin();
        currentRoad != end();
        currentRoad++)
  {
    // Check for intersection
    if (roadPath.crosses(*(*currentRoad)->path(), &intersection))
    {

      if (intersection == roadPath.begining() ||
          intersection == roadPath.end())
      /* New road is just touching some other one */
      {
      }
      else
      {
        Path firstPart(LineSegment(roadPath.begining(), intersection)),
              secondPart(LineSegment(intersection, roadPath.end()));
        addRoad(firstPart, roadType);
        addRoad(secondPart, roadType);

        return;
      }
    }
  }

  Intersection *begining = addIntersection(roadPath.begining());
  Intersection *end = addIntersection(roadPath.end());

  Road *newRoad = new Road(begining, end);
  newRoad->setType(roadType);
  //newRoad->setPath(roadPath);

  // Connect road to intersections
  begining->addRoad(newRoad);
  end->addRoad(newRoad);

  roads->push_back(newRoad);

  return;
}

void StreetGraph::removeRoad(Road* road)
{
  Intersection* begining = road->begining();
  Intersection* end = road->end();

  begining->removeRoad(road);
  if (begining->numberOfWays() == 0)
  {
    intersections->remove(begining);
    delete begining;
  }

  end->removeRoad(road);
  if (end->numberOfWays() == 0)
  {
    intersections->remove(end);
    delete end;
  }

  roads->remove(road);
}

Intersection* StreetGraph::addIntersection(Point const& position)
{
  /* Search for existing intersection. */
  for (std::list<Intersection*>::iterator intersection = intersections->begin();
       intersection != intersections->end();
       intersection++)
  {
    if ((*intersection)->position() == position)
    {
      return *intersection;
    }
  }

  /* There's no existing intersection at position. Create one */
  Intersection *newIntersection = new Intersection(position);
  intersections->push_back(newIntersection);

  //debug("StreetGraph::addIntersection(): Adding intersection Intersection " << newIntersection->position().toString());

  /* Check if the existing intersection crosses any existing road. */
  for (std::list<Road*>::iterator road = roads->begin();
       road != roads->end();
       road++)
  {
    if ((*road)->path()->goesThrough(position))
    /* If so, split the road into two. */
    {
      //debug("StreetGraph::addIntersection(): Splitting road for Intersection " << newIntersection->position().toString());
      Intersection *end = (*road)->end();
      end->removeRoad(*road);

      (*road)->setEnd(newIntersection);
      newIntersection->addRoad(*road);

      Road* secondPart = new Road(newIntersection, end);
      secondPart->setType((*road)->type());
      roads->push_back(secondPart);

      newIntersection->addRoad(secondPart);
      end->addRoad(secondPart);
      break;
    }
  }

  return newIntersection;
}

StreetGraph::iterator StreetGraph::begin()
{
  return roads->begin();
}

StreetGraph::iterator StreetGraph::end()
{
  return roads->end();
}

bool StreetGraph::isIntersectionAtPosition(Point const& position)
{
  /* Search for existing intersection. */
  for (std::list<Intersection*>::iterator intersection = intersections->begin();
       intersection != intersections->end();
       intersection++)
  {
    if ((*intersection)->position() == position)
    {
      return true;
    }
  }

  return false;
}

Intersection* StreetGraph::getIntersectionAtPosition(Point const& position)
{
  /* Search for existing intersection. */
  for (std::list<Intersection*>::iterator intersection = intersections->begin();
       intersection != intersections->end();
       intersection++)
  {
    if ((*intersection)->position() == position)
    {
      return (*intersection);
    }
  }

  return 0;
}

int StreetGraph::numberOfRoads()
{
  return roads->size();
}


StreetGraph::Intersections StreetGraph::getIntersections()
{
  return *intersections;
}

StreetGraph::Roads StreetGraph::getRoads()
{
  return *roads;
}

std::string StreetGraph::toString()
{
  std::stringstream output;
  output << "Roads:\n";
  for (Roads::iterator road = roads->begin();
       road != roads->end();
       road++)
  {
    output << "  " << (*road) << "\n";
    output << "    from " << (*road)->begining() << " to " << (*road)->end() << "\n";
    output << "    " + (*road)->path()->toString() + "\n";
  }

  output << "Intersections:\n";
  for (Intersections::iterator intersection = intersections->begin();
       intersection != intersections->end();
       intersection++)
  {
    output << "  " << (*intersection) << "\n";
    output << "    at " + (*intersection)->position().toString() + "\n";

    Roads intersectionRoads = (*intersection)->getRoads();
    for (Roads::iterator road = intersectionRoads.begin();
      road != intersectionRoads.end();
      road++)
    {
      output << "    " << (*road) << "\n";
    }
  }

  return output.str();
}