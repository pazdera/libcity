/**
 * This code is part of libcity library.
 *
 * @file streetgraph/intersection.h
 * @date 02.03.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @brief Intersection of N roads
 *
 *
 */

#ifndef _INTERSECTION_H_
#define _INTERSECTION_H_

#include <list>
#include <vector>

class Point;
class Road;

class Intersection
{
  private:
    Intersection();

  public:
    Intersection(Point coordinates);
    ~Intersection();

    Point position() const;
    void  setPosition(Point const& coordinates);

    std::vector<Intersection*> adjacentIntersections();
    int  numberOfWays() const; /**< Number of ways of the intersection */

    void addRoad(Road* road) throw();
    void removeRoad(Road* road);

    bool hasRoad(Road* road);

    std::list<Road*> getRoads();

  private:
    std::list<Road*>* roads;     /**< Topological information */
    Point* geometrical_position; /**< Geometrical information */
};


#endif
