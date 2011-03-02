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

class Intersection;
class Road;

class StreetGraph
{
  public:
    StreetGraph();
    ~StreetGraph();

  private:
    /** All intersections in the street graph. */
    std::list<Intersection> *intersections;

    /** All roads in the street graph.
        This is not neccessary, but could be
        useful. */
    std::list<Road> *roads;
};

#endif