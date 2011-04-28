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
  protected:
    //Polygon* constraints;
    Area* parentArea;

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
    Edge *polygonGraph;
    Edge* constructPolygonGraph(Polygon const& polygon);
    Polygon constructPolygon(Edge* graph);
    Edge* copyPolygonGraph(Edge* source);

  public:
    Area();
    virtual ~Area();

    Area(Area const& source);
    Area& operator=(Area const& source);

    virtual void setAreaConstraints(Polygon const& area);
    virtual void setAreaConstraints(Edge* polygonGraphRepresentation);
    virtual Polygon areaConstraints();
    virtual Edge* getPolygonGraph();
    virtual Edge* getPolygonGraphCopy();
    Edge* insertToPolygonGraph(Edge* after, Point const& begining);
    void bridge(Edge* first, Edge* second);

    virtual void setParent(Area* area);
    virtual Area* parent();

    bool hasRoadAccess();
    Edge* getLongestEdgeWithRoadAccess();
    Edge* getLongestEdgeWithoutRoadAccess();

  private:
    void initialize();
    void freeMemory();
};

#endif