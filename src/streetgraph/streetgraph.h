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

    /** @{ */
    /** For iterating through the roads of StreetGraph. */
    typedef std::list<Road*>::iterator iterator;
    iterator begin();
    iterator end();
    /** @} */

    /**
      Find closed loops in the graph and form zones inside them.
     @remarks
       This is done by finding minimal cycle basis of the graph.
       StreetGraph is copied into a more suitable data structure
       in the process.
     @note
       The algorithm used is David Eberly's implementation for
       planar graphs.
       http://www.mpi-inf.mpg.de/~mehlhorn/ftp/MFCS07.pdf
       @see MinimalCycleBasis

     @return List of pointers to all zones found.
     */
    std::list<Zone*> findZones();

    /**
      Add road that follows certain path into the StreetGraph.
     @remarks
       This method makes sure that the graph is planar so
       more than one road may be added at a time. If an
       intersection with an existing road is detected,
       the new road is split into two.
     @todo
       Clarify connecting Roads with Intersections and
       synchronising both levels of the graph. Beware
       this is source of particularly horrible bugs.

     @param path Path of the new road (low level part of the graph).
    */
    void addRoad(Path const& path);

    /**
      Erase road from the StreetGraph.
     @remarks
       Road is disconnected from both Intersections. If
       there is no use for them (they have no roads leading
       to them) they will be removed as well.

     @param road Road to remove.
    */
    void removeRoad(Road* road);

    /**
      Number of all roads currently in StreetGraph.
     @remarks
       Don't use for iterating through the graph. It's
       for statistical/debugging purposes only.
     */
    int numberOfRoads();

    bool isIntersectionAtPosition(Point const& position);

  private:
    Intersection* addIntersection(Point const& position);

    /** All intersections in the street graph. */
    std::list<Intersection*> *intersections;

    /** All roads in the street graph. */
    std::list<Road*> *roads;

    void initialize();
    void freeMemory();
};

#endif