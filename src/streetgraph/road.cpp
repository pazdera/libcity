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
#include "../debug.h"
#include "path.h"
#include "intersection.h"
#include "../geometry/line.h"
#include "../geometry/point.h"

Road::Road()
  : from(0), to(0), geometrical_path(0)
{
  geometrical_path = new Path;
}

Road::Road(Intersection *first, Intersection *second)
  : from(first), to(second), geometrical_path(0)
{
  geometrical_path = new Path(Line(from->position(), to->position()));
}

Road::Road(Path const& path)
  : from(0), to(0), geometrical_path(0)
{
  geometrical_path = new Path(path);
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

void Road::setPath(Path const& roadPath) throw()
{
  //TODO: check if the path start and end matches the intersections
  delete geometrical_path;
  geometrical_path = new Path(roadPath);
}

void Road::estimatePath()
{
  if (geometrical_path != 0)
  {
    delete geometrical_path;
  }

  geometrical_path = new Path(Line(from->position(), to->position()));
}

Road::types Road::type()
{
  return roadType;
}

void Road::setType(Road::types type)
{
  roadType = type;
}

void Road::setBegining(Intersection* intersection)
{
  from = intersection;
  geometrical_path->setBegining(from->position());
}

void Road::setEnd(Intersection* intersection)
{
  to = intersection;
  geometrical_path->setEnd(to->position());
}

Path* Road::path() const
{
  return geometrical_path;
}