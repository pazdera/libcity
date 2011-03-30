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
#include "path.h"
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
  roads = new std::list<Road*>;
  intersections = new std::list<Intersection*>;
  zones = new std::vector<StreetGraph*>;;
}

StreetGraph::~StreetGraph()
{
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

StreetGraph* StreetGraph::zone(int number) const
{
  return zones->at(number);
}

int StreetGraph::numberOfZones() const
{
  return zones->size();
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

bool StreetGraph::addRoad(Path const& path, Point* modifiedEndPoint)
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


  if(!isPathInsideAreaConstraints(roadPath))
  {
    return false;
  }

  roadPath.trimOverlapingPart(*areaConstraints);

  Intersection* nearestIntersection = 0;
  double distanceToNearestIntersection = libcity::SNAP_DISTANCE + 1;

  Road* nearestRoad = 0;
  double distanceToNearestRoad = libcity::SNAP_DISTANCE + 1;

  Point intersection;
  double distance;
  for (std::list<Road*>::iterator currentRoad = roads->begin();
       currentRoad != roads->end();
       currentRoad++)
  {
    // Check for intersection
    if (roadPath.crosses(*(*currentRoad)->path(), &intersection))
    {
      addIntersection(intersection);

      if (intersection == roadPath.begining() ||
          intersection == roadPath.end())
      /* New road is just touching some other one */
      {
      }
      else
      {
        Path firstPart(Line(roadPath.begining(), intersection)),
             secondPart(Line(intersection, roadPath.end()));
        return addRoad(firstPart, modifiedEndPoint);
      }
    }

    // Measure distance of ending point of the path
    //   - to intersection and to the whole path
    distance = Vector(roadPath.end(), (*currentRoad)->begining()->position()).length();
    if (distance < libcity::SNAP_DISTANCE && distance < distanceToNearestIntersection)
    {
      nearestIntersection = (*currentRoad)->begining();
    }

    distance = Vector(roadPath.end(), (*currentRoad)->end()->position()).length();
    if (distance < libcity::SNAP_DISTANCE && distance < distanceToNearestIntersection)
    {
      nearestIntersection = (*currentRoad)->end();
    }

    distance = Vector(roadPath.end(), (*currentRoad)->path()->nearestPoint(roadPath.end())).length();
    if (distance < libcity::SNAP_DISTANCE && distance < distanceToNearestRoad)
    {
      nearestRoad = (*currentRoad);
    }

    // Measure similarity of the two paths
    // roadpath is too close to some existing path
    if (roadPath.distance((*currentRoad)->end()->position()) < libcity::SNAP_DISTANCE &&
        roadPath.distance((*currentRoad)->begining()->position()) < libcity::SNAP_DISTANCE
       )
    {
      return false;
    }

    // Some existing road is too close
    if ((*currentRoad)->path()->distance(roadPath.begining()) < libcity::SNAP_DISTANCE &&
        (*currentRoad)->path()->distance(roadPath.end()) < libcity::SNAP_DISTANCE
       )
    {
      return false;
    }
  }

  if (nearestIntersection != 0)
  {
    roadPath.setEnd(nearestIntersection->position());
  }
  else
  {
    if (nearestRoad != 0)
    {
      roadPath.setEnd(nearestRoad->path()->nearestPoint(roadPath.end()));
    }
  }

  Intersection *begining = addIntersection(roadPath.begining());
  Intersection *end = addIntersection(roadPath.end());
  Road *newRoad = new Road(begining, end);
  newRoad->setPath(roadPath);

  *modifiedEndPoint = roadPath.end();
  roads->push_back(newRoad);
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
    if ((*currentRoad)->path()->goesThrough(position))
    {
      Intersection *end = (*currentRoad)->end();
      (*currentRoad)->setEnd(middle);
      roads->push_back(new Road(middle, end));
      break;
    }
  }

  return middle;
}

bool StreetGraph::isPathInsideAreaConstraints(Path const& proposedPath)
{
  bool beginingIsInside = areaConstraints->encloses2D(proposedPath.begining()),
       endIsInside = areaConstraints->encloses2D(proposedPath.end());

  return beginingIsInside || endIsInside;
}
