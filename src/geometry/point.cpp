/**
 * This code is part of libcity library.
 *
 * @file geometry/point.cpp
 * @date 19.02.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @see geometry/point.h
 *
 */

#include "point.h"

Point::Point()
  : xPosition(0), yPosition(0), zPosition(0)
{}

Point::Point(int x, int y)
  : xPosition(x), yPosition(y), zPosition(0)
{}

Point::Point(int x, int y, int z)
  : xPosition(x), yPosition(y), zPosition(z)
{}

Point::~Point()
{}

int Point::x() const
{
  return xPosition;
}

int Point::y() const
{
  return yPosition;
}

int Point::z() const
{
  return zPosition;
}

void Point::setX(int coordinate)
{
  xPosition = coordinate;
}

void Point::setY(int coordinate)
{
  yPosition = coordinate;
}

void Point::setZ(int coordinate)
{
  zPosition = coordinate;
}
