/**
 * This code is part of libcity library.
 *
 * @file streetgraph.h
 * @date 17.02.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @brief Street graph representation
 *
 * Roads and Intersections form together an undirected
 * plannar graph. There are two levels of the graph.
 *
 * On a *topological* level, the streetgraph says where
 * a certain road begins and where it leads to.
 * On the lower level, the *geometrical* level, the graph
 * says where exactly in the space are the topological
 * elements (Intersection, Roads) located by specifying
 * position (Point) for an intersection and path (Line)
 * for a road.
 *
 */

#ifndef _STREETGRAPH_H_
#define _STREETGRAPH_H_

#include <list>
#include <map>
#include <vector>
#include <set>

class Intersection;
class Road;
class Zone;
class Point;
class Polygon;
class Path;
class Line;

class StreetGraph
{
  public:
    StreetGraph();
    ~StreetGraph();

    /**
     * For iterating through the roads of StreetGraph.
     */
    typedef std::list<Road*>::iterator iterator;
    iterator begin();
    iterator end();

    /**
     * Find closed loops in the graph and form zones inside
     * them.
     */
    std::list<Zone*> findZones();

    void addRoad(Path const& path);
    void removeRoad(Road* road);

    bool isIntersectionAtPosition(Point const& position);

  private:
    Intersection* addIntersection(Point const& position);

    /** All intersections in the street graph. */
    std::list<Intersection*> *intersections;

    /** All roads in the street graph.
        This is not neccessary, but could be
        useful. */
    std::list<Road*> *roads;

    void initialize();
    void freeGraph();
};

#endif