/**
 * This code is part of libcity library.
 *
 * @file area/region.h
 * @date 28.04.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @brief Area implementation using directed polygon graphs.
 *
 */

#ifndef _REGION_H_
#define _REGION_H_

/* STL */
#include <vector>
#include <list>
#include <map>

/* libcity */
#include "../geometry/point.h"

class Polygon;
class StreetGraph;
class RoadLSystem;
class Intersection;
class Block;
class LineSegment;

class Region
{
  public:
    struct Edge;
    struct Edge
    {
      Point begining;
      double s;
      bool hasRoadAccess;
      Edge* previous;
      Edge* next;

      bool operator<(Edge* second) { return s < second->s; }
    };

    Region();
    Region(Edge* edge);
    Region(Polygon const& polygon);
    ~Region();

    Region(Region const& source);
    Region& operator=(Region const& source);

    Edge* getFirstEdge();
    Edge* insert(Edge* after, Point const& begining);
    void bridge(Edge* first, Edge* second);

    bool hasRoadAccess();
    Edge* getLongestEdgeWithRoadAccess();
    Edge* getLongestEdgeWithoutRoadAccess();

    Polygon toPolygon();
  private:
    Edge *polygonGraph;

    Edge* insertFirst(Point const& begining);
    Edge* constructPolygonGraph(Polygon const& polygon);
    Edge* copyPolygonGraph(Edge* source);

    void initialize();
    void freeMemory();
};

#endif