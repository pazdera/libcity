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
#include "minimalcyclebasis.h"
#include "../lsystem/roadlsystem.h"
#include "../geometry/polygon.h"
#include "../geometry/line.h"
#include "../geometry/point.h"
#include "../geometry/vector.h"
#include "../geometry/units.h"
#include "../debug.h"

#include <set>

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
    if (removedIntersection->owner() == this)
    {
      delete removedIntersection;
    }
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
  MinimalCycleBasis graph(intersections);
  std::list<Polygon> boundaries = graph.getMinimalCycles();

  std::list<Zone*> zones;
  debug("StreetGraph::findZones() found " << boundaries.size() << " zones.");

  for (std::list<Polygon>::iterator foundZone = boundaries.begin();
       foundZone != boundaries.end();
       foundZone++)
  {
    Zone* newZone = new Zone(this);
    newZone->setAreaConstraints(*foundZone);
    zones.push_back(newZone);
  }

  return zones;
}


void StreetGraph::addRoad(Path const& path)
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
        Path firstPart(Line(roadPath.begining(), intersection)),
              secondPart(Line(intersection, roadPath.end()));
        addRoad(firstPart);
        addRoad(secondPart);
      }
    }
  }

  Intersection *begining = addIntersection(roadPath.begining());
  Intersection *end = addIntersection(roadPath.end());

  Road *newRoad = new Road(begining, end);
  //newRoad->setPath(roadPath);

  // Connect road to intersections
  begining->addRoad(newRoad);
  end->addRoad(newRoad);

  roads->push_back(newRoad);
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

int StreetGraph::numberOfRoads()
{
  return roads->size();
}