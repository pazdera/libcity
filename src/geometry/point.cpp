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

Point::Point(double x, double y)
  : xPosition(x), yPosition(y), zPosition(0)
{}

Point::Point(double x, double y, double z)
  : xPosition(x), yPosition(y), zPosition(z)
{}

Point::~Point()
{}

void Point::set(double xCoord, double yCoord, double zCoord)
{
  xPosition = xCoord;
  yPosition = yCoord;
  zPosition = zCoord;
}

bool Point::operator==(Point const& second)
{
  return xPosition == second.x() && yPosition == second.y() && zPosition == second.z();
}

bool Point::operator<(Point const& second)
{
  if (x() < second.x())
  {
    return true;
  }
  else if (x() == second.x())
  {
    return y() < second.y();
  }

  return false;
}

bool Point::operator>(Point const& second)
{
  if (x() > second.x())
  {
    return true;
  }
  else if (x() == second.x())
  {
    return y() > second.y();
  }

  return false;
}


// Point::operator std::string()
// {
//   return "(" << xPosition << ", " << yPosition << ", " << zPosition << ")";
// }