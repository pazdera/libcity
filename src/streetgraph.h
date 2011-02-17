/**
 * This code is part of libcity library.
 *
 * @file streetgraph.h
 * @date 17.02.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @brief Classes for street graph representation
 *
 */

#ifndef _STREETGRAPH_H_
#define _STREETGRAPH_H_

class Intersection
{
  public:
    Intersection();
    ~Intersection();

  private:
    Point *position;
    Road  roads;
};

class Road
{
  public:
    Road();
    ~Road();

  private:
    
};

#endif