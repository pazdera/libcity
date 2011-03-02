/**
 * This code is part of libcity library.
 *
 * @file streetgraph/road.cpp
 * @date 02.03.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @see road.h
 *
 */

#include "road.h"
#include "intersection.h"
#include "../geometry/line.h"

/** No places (intersections), no path between them.
    There's no use for such object. */
Road::Road()
  : from(0), to(0), geometrical_path(0)
{}

Road::Road(Intersection *first, Intersection *second)
  : from(first), to(second), geometrical_path(0)
{
  geometrical_path = new Line();
}

Road::~Road()
{
  /* "from", "to" are NOT free'd here,
     because they were not allocated by this object. */

  if (geometrical_path != 0)
  {
    delete geometrical_path;
  }
}

void Road::setPath(Line& roadPath) throw()
{
  //TODO: check if the path start and end matches the intersections
  delete geometrical_path;
  geometrical_path = new Line(roadPath);
}