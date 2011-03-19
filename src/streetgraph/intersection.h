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

class Point; //!< From geometry package
class Road;

class Intersection
{
  private:
    Intersection();

  public:
    Intersection(Point coordinates);

    ~Intersection();

    Point position() const;
    void  setPosition(Point coordinates);

    int  numberOfWays() const; /**< Number of ways of the intersection */
    void addRoad(Road* road) throw();

    void* owner();
    void  setOwner(void* ownerObject);
  private:
    std::list<Road*> *roads;     /**< Topological information */
    Point *geometrical_position; /**< Geometrical information */

    void* belongsTo;
};


#endif
