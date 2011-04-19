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
#include <string>

class Intersection;
class Road;
class Zone;
class Point;
class Polygon;
class Path;
class LineSegment;

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

    typedef std::list<Intersection*> Intersections;
    typedef std::list<Road*> Roads;

    Intersections getIntersections();
    Roads getRoads();

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

     @param[in] path Path of the new road (low level part of the graph).
    */
    void addRoad(Path const& path);

    /**
      Erase road from the StreetGraph.
     @remarks
       Road is disconnected from both Intersections. If
       there is no use for them (they have no roads leading
       to them) they will be removed as well.

     @param[in,out] road Road to remove. Variable will have
                         undefined value after deleting the road.
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

    std::string toString();

  private:
    /** All intersections in the street graph. */
    Intersections* intersections;

    /** All roads in the street graph. */
    Roads* roads;

    /**
      Method for adding new intersections to the graph.
     @remarks
       If some intersection exists at the target position
       no intersection is added (the existing one is returned).
       Also if the new intersection resides on existing
       road, the road will be split it in two and connected
       through the new intersection.
     @param[in] position Where to put the intersection.
     @return Intersection at position specified by point (new or existing).
     */
    Intersection* addIntersection(Point const& position);

    void initialize();
    void freeMemory();
};

#endif