/**
 * This code is part of libcity library.
 *
 * @file streetgraph/intersection.cpp
 * @date 02.03.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @see intersection.h
 *
 */

#include "intersection.h"
#include "road.h"
#include "../debug.h"
#include "../geometry/point.h"

Intersection::Intersection()
  : roads(0), geometrical_position(0)
{
}

Intersection::Intersection(Point coordinates)
  : roads(0), geometrical_position(0)
{
  geometrical_position = new Point(coordinates);
  roads = new std::list<Road*>;
}

Intersection::~Intersection()
{
  if (geometrical_position != 0)
  {
    delete geometrical_position;
  }

  if (roads != 0)
  {
    delete roads;
  }
}

std::vector<Intersection*> Intersection::adjacentIntersections()
{
  std::vector<Intersection*> adjacent;
  adjacent.clear();

  for (std::list<Road*>::iterator adjacentRoadIterator = roads->begin();
       adjacentRoadIterator != roads->end();
       adjacentRoadIterator++)
  {
    if ((*adjacentRoadIterator)->begining() != this)
    {
      adjacent.push_back((*adjacentRoadIterator)->begining());
    }
    else
    {
      adjacent.push_back((*adjacentRoadIterator)->end());
    }
  }

//   debug("Intersection::adjacentIntersections(): has " << numberOfWays() << " ways.");
//   debug("Intersection::adjacentIntersections(): returns " << adjacent.size() << " adjacent intersections.");
  return adjacent;
}

void Intersection::connectRoad(Road* road) throw()
{
  if (road->begining()->position() == *geometrical_position ||
      road->end()->position()      == *geometrical_position)
  {
    roads->push_back(road);
  }
  else
  {
    // TODO: error
  }
}


void Intersection::disconnectRoad(Road* road)
{
  roads->remove(road);
}

Point Intersection::position() const
{
  return *geometrical_position;
}

void Intersection::setPosition(Point const& coordinates)
{
  *geometrical_position = coordinates;
}

int Intersection::numberOfWays() const
{
  return roads->size();
}

std::list<Road*> Intersection::getRoads()
{
  return *roads;
}

bool Intersection::hasRoad(Road* road)
{
  for (std::list<Road*>::iterator roadIterator = roads->begin();
       roadIterator != roads->end();
       roadIterator++)
  {
    if (*roadIterator == road)
    {
      return true;
    }
  }

  return false;
}