/**
 * This code is part of libcity library.
 *
 * @file area/area.cpp
 * @date 26.04.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @see area.h
 *
 */

#include "area.h"

#include "../debug.h"
#include "../geometry/units.h"
#include "../geometry/point.h"
#include "../geometry/polygon.h"
#include "../geometry/vector.h"

Area::Area()
{
  initialize();
}

Area::Area(Area const& source)
{
  initialize();

  *constraints = *(source.constraints);
  parentArea = source.parentArea;
}

void Area::initialize()
{
  parentArea = 0;
  constraints = new Polygon();
}

Area& Area::operator=(Area const& source)
{
  *constraints = *(source.constraints);
  parentArea = source.parentArea;

  return *this;
}

Area::~Area()
{
  freeMemory();
}

void Area::freeMemory()
{
  delete constraints;
}

Polygon Area::areaConstraints()
{
  return *constraints;
}

void Area::setAreaConstraints(Polygon const& area)
{
  *constraints = area;
}

void  Area::setParent(Area* area)
{
  parentArea = area;
}

Area* Area::parent()
{
  return parentArea;
}