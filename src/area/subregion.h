/**
 * This code is part of libcity library.
 *
 * @file area/subregion.h
 * @date 28.04.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @brief Area implementation using directed polygon graphs.
 *
 */

#ifndef _SUBREGION_H_
#define _SUBREGION_H_

/* STL */
#include <vector>
#include <list>
#include <map>
#include <string>

/* libcity */
#include "../geometry/point.h"

class Polygon;
class StreetGraph;
class RoadLSystem;
class Intersection;
class Block;
class LineSegment;
class Point;

class SubRegion
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

      bool operator<(Edge* second) { return begining < second->begining; }
    };

    SubRegion();
    SubRegion(Edge* edge);
    SubRegion(Polygon const& polygon);
    ~SubRegion();

    SubRegion(SubRegion const& source);
    SubRegion& operator=(SubRegion const& source);

    Edge* getFirstEdge();
    Edge* insert(Edge* after, Point const& begining);
    void bridge(Edge* first, Edge* second);

    bool hasRoadAccess();
    Edge* getLongestEdgeWithRoadAccess();
    Edge* getLongestEdgeWithoutRoadAccess();

    Polygon toPolygon();
    std::string toString();
  private:
    Edge *polygonGraph;

    Edge* insertFirst(Point const& begining);
    Edge* constructPolygonGraph(Polygon const& polygon);
    Edge* copyPolygonGraph(Edge* source);

    void initialize();
    void freeMemory();
};

#endif