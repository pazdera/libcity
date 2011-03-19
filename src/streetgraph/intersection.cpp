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
#include "../geometry/point.h"

Intersection::Intersection()
  : roads(0), geometrical_position(0)
{}

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

void Intersection::addRoad(Road* road) throw()
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

Point Intersection::position() const
{
  return *geometrical_position;
}

void Intersection::setPosition(Point coordinates)
{
  *geometrical_position = coordinates;
}

int Intersection::numberOfWays() const
{
  return roads->size();
}

void* Intersection::owner()
{
  return belongsTo;
}

void Intersection::setOwner(void* ownerObject)
{
  belongsTo = ownerObject;
}