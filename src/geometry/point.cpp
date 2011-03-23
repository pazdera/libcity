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
#include "units.h"

#include <sstream>
#include <string>
#include <cmath>

Point::Point()
  : xPosition(0), yPosition(0), zPosition(0)
{}

Point::Point(double const& x, double const& y)
  : xPosition(x), yPosition(y), zPosition(0)
{}

Point::Point(double const& x, double const& y, double const& z)
  : xPosition(x), yPosition(y), zPosition(z)
{}

Point::Point(Point const& source)
{
  xPosition = source.x();
  yPosition = source.y();
  zPosition = source.z();
}

Point::~Point()
{}

void Point::set(double const& xCoord, double const& yCoord, double const& zCoord)
{
  xPosition = xCoord;
  yPosition = yCoord;
  zPosition = zCoord;
}

bool Point::operator==(Point const& second)
{
  return std::abs(xPosition - second.x()) < libcity::EPSILON &&
         std::abs(yPosition - second.y()) < libcity::EPSILON &&
         std::abs(zPosition - second.z()) < libcity::EPSILON;
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

std::string Point::toString()
{
  std::stringstream convertor;
  convertor << "Point(" << xPosition << ", " << yPosition << ", " << zPosition << ")";
  return convertor.str();
}