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
#include "../geometry/line.h"
#include "../geometry/point.h"

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

StreetGraph* StreetGraph::zone(int number) const
{
  return zones->at(number);
}

int StreetGraph::numberOfZones() const
{
  return zones->size();
}

void StreetGraph::populate()
{
  /* while (getNextRoadSegment())
   * addRoad()
   * accept/decline
   */
}

void StreetGraph::divideToZones()
{
  /* find loops in graph
   * for each zone
   *   construct streetgraph
   *   set it to zone
   *   add boundary roads to the zone
   *   set area constraints of the zone
   */
}

Road* StreetGraph::addRoad(Path* roadPath)
{
  /* check for areaConstraints
   * if begining or end are out of the areaConstraints
   *   find breaking point
   *   shorten the path so it fits
   *
   * check for any crossings with existing roads
   * if the new path intersects with some existing road
   *   add new intersection
   *   split up both roads
   *   connect existing road to intersection
   *   call addRoad for the two new segments
   *
   * check for intersections in positions of begining and end of the road
   * if they exists
   *   add road to the intersections
   * else
   *   create new intersections
   *   connect road to the intersections
   */
  bool beginingIsInside = areaConstraints->hasPoint2D(roadPath->begining()),
       endIsInside = areaConstraints->hasPoint2D(roadPath->end());

  if (!beginingIsInside && !endIsInside)
  /* Out of the constraints completely */
  {
    return 0;
  }

  if (!beginingIsInside)
  {
    // cut it
    // Projit hrany polygonu, najit tu, se ktrou se protina
    // prusecik = novy bod
  }

  if (!endIsInside)
  {
    // cut it
  }

  return 0;
}

Intersection* StreetGraph::addIntersection(Point* position)
{
  /* Check for any existing intersections/roads
   * if (road exists in the place)
   *   divide it in two roads
   *   place intersection
   *   connect divided roads
   * else if (intersection exists in the place)
   *   do nothing
   *   return existing
   * else
   *   place intersection
   *   return it
   */

  return 0;
}
