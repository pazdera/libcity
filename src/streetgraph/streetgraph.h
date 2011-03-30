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
#include <vector>

class Intersection;
class Road;
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
     * Define area constraints for the graph.
     * All roads will be generated inside these
     * borders.
     */
    void setAreaConstraints(Polygon* polygon);

    /**
     * Find closed loops in the graph and form zones inside
     * them.
     */
    void divideToZones();

    int  numberOfZones() const;
    StreetGraph* zone(int number) const;

    bool addRoad(Path const& path, Point* modifiedEndPoint);
    Intersection* addIntersection(Point const& position);

  private:
    /** All intersections in the street graph. */
    std::list<Intersection*> *intersections;

  public: // FIXME
    /** All roads in the street graph.
        This is not neccessary, but could be
        useful. */
    std::list<Road*> *roads;

  private:
    Polygon* areaConstraints;

    std::vector<StreetGraph*> *zones;

    bool isPathInsideAreaConstraints(Path const& proposedPath);

    void initialize();
    void freeAreaConstraints();
    void freeZones();
    void freeGraph();
};

#endif