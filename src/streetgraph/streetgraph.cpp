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
#include "../lsystem/roadlsystem.h"
#include "../geometry/polygon.h"

StreetGraph::StreetGraph()
{
  initialize();
}

void StreetGraph::initialize()
{
  areaConstraints = 0;
  roadNetworkGenerator = 0;
  roads = new std::list<Road*>;
  intersections = new std::list<Intersection*>;
  zones = new std::vector<StreetGraph*>;;
}

StreetGraph::~StreetGraph()
{
  freeRoadNetworkGenerator();
  freeAreaConstraints();
  freeZones();
  freeGraph();
}

void StreetGraph::freeZones()
{
  while (!zones->empty())
  {
    delete zones->back();
    zones->pop_back();
  }

  delete zones;
}

void StreetGraph::freeGraph()
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

  while (!roads->empty())
  {
    removedRoad = roads->back();
    if (removedRoad->owner() == this)
    {
      delete removedRoad;
    }
    roads->pop_back();
  }
}

void StreetGraph::setAreaConstraints(Polygon *polygon)
{
  freeAreaConstraints();
  areaConstraints = polygon;
}

void StreetGraph::freeAreaConstraints()
{
  if (areaConstraints != 0)
  {
    delete areaConstraints;
  }
}

void StreetGraph::setRoadNetworkGenerator(RoadLSystem *generator)
{
  freeRoadNetworkGenerator();
  roadNetworkGenerator = generator;
}

void StreetGraph::freeRoadNetworkGenerator()
{
  if (roadNetworkGenerator != 0)
  {
    delete roadNetworkGenerator;
  }
}

StreetGraph* StreetGraph::zone(int number)
{
  return zones->at(number);
}

int StreetGraph::numberOfZones()
{
  return zones->size();
}

void StreetGraph::populate()
{

}

void StreetGraph::divideToZones()
{

}

void StreetGraph::addRoad(Road* road)
{
  /* check for areaConstraints
   * if begining or end are out of the areaConstraints
   *   cut the path so it fits
   *
   * check for intersections in positions of begining and end of the road
   * if they exists
   *   add road to the intersections
   * else
   *   create new intersections
   *
   * check for crossings
   * if the new path intersects with some existing road
   *   add new intersections along the way
   */
}
