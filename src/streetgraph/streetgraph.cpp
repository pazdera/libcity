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
#include "../geometry/vector.h"
#include "../geometry/units.h"
#include "../debug.h"

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
  delete intersections;

  while (!roads->empty())
  {
    removedRoad = roads->back();
    if (removedRoad->owner() == this)
    {
      delete removedRoad;
    }
    roads->pop_back();
  }
  delete roads;
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
  // FIXME
  Path newRoadSegment;
  for (int roads = 0; roads<1000; roads++)
  {
    newRoadSegment = roadNetworkGenerator->getNextIdealRoadSegment();
//     debug(newRoadSegment.toString());
    debug(addRoad(newRoadSegment));
  }
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

bool StreetGraph::addRoad(Path const& path)
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
  Path roadPath(path);
  bool beginingIsInside = areaConstraints->encloses2D(roadPath.begining()),
       endIsInside = areaConstraints->encloses2D(roadPath.end());

  if (!beginingIsInside && !endIsInside)
  /* Out of the constraints completely */
  {
    return false;
  }

  if (!beginingIsInside || !endIsInside)
  {
    roadPath.trimOverlapingPart(*areaConstraints);
  }

  Point intersection;
  for (std::list<Road*>::iterator currentRoad = roads->begin();
       currentRoad != roads->end();
       currentRoad++)
  {

    if (roadPath.intersection2D(*(*currentRoad)->path(), &intersection) == Line::INTERSECTING)
    {
      addIntersection(intersection);

      if (intersection == roadPath.begining() ||
          intersection == roadPath.end())
      /* New road is just touching some other one */
      {
        continue;
        //return addRoad(roadPath);
      }
      else
      {
        debug("Cykl:");
        debug((*currentRoad)->path()->toString());
        debug(roadPath.toString());
        debug(intersection.toString());
        Path firstPart(roadPath.begining(), intersection),
             secondPart(intersection, roadPath.end());
        debug(firstPart.toString());
        debug(secondPart.toString());
        return addRoad(firstPart) && addRoad(secondPart);
      }
    }
  }

  // The snap
  for (std::list<Road*>::iterator currentRoad = roads->begin();
       currentRoad != roads->end();
       currentRoad++)
  {
    if (Vector(roadPath.end(), (*currentRoad)->path()->begining()).length() < libcity::SNAP_DISTANCE)
    {
      roadPath.setEnd((*currentRoad)->path()->begining());
      break;
    }

    if (Vector(roadPath.end(), (*currentRoad)->path()->end()).length() < libcity::SNAP_DISTANCE)
    {
      roadPath.setEnd((*currentRoad)->path()->end());
      break;
    }
  }

  Intersection *begining = addIntersection(roadPath.begining());
  Intersection *end = addIntersection(roadPath.end());

  roads->push_back(new Road(begining, end));
  return true;
}

Intersection* StreetGraph::addIntersection(Point const& position)
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
  for (std::list<Intersection*>::iterator currentIntersection = intersections->begin();
       currentIntersection != intersections->end();
       currentIntersection++)
  {
    if ((*currentIntersection)->position() == position)
    {
      return *currentIntersection;
    }
  }

  Intersection *middle = new Intersection(position);
  intersections->push_back(middle);
  for (std::list<Road*>::iterator currentRoad = roads->begin();
       currentRoad != roads->end();
       currentRoad++)
  {
    if ((*currentRoad)->path()->hasPoint2D(position))
    {
      Intersection *end = (*currentRoad)->end();
      (*currentRoad)->setEnd(middle);
      roads->push_back(new Road(middle, end));
      break;
    }
  }

  return middle;
}
