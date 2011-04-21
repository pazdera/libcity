/**
 * This code is part of libcity library.
 *
 * @file geometry/ray.cpp
 * @date 15.04.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @see geometry/ray.h
 *
 */

#include "ray.h"
#include "point.h"
#include "vector.h"
#include "line.h"
#include "units.h"
#include "../debug.h"

#include <cmath>

Ray::Ray()
{
  initialize();
  rayOrigin->set(0,0,0);
  rayDirection->set(1,0,0);
}

Ray::Ray(Point const& point, Vector const& vector)
{
  initialize();
  *rayOrigin = point;
  *rayDirection = vector;
}

Ray::Ray(Point const& firstPoint, Point const& secondPoint)
{
  initialize();
  *rayOrigin = firstPoint;
  *rayDirection = Vector(firstPoint, secondPoint);
}

Ray::Ray(Ray const& source)
{
  initialize();
  *rayOrigin = source.origin();
  *rayDirection = source.direction();
}

Ray& Ray::operator=(Ray const& source)
{
  *rayOrigin = source.origin();
  *rayDirection = source.direction();
  return *this;
}

void Ray::initialize()
{
  rayOrigin = new Point();
  rayDirection = new Vector();
}

Ray::~Ray()
{
  freeMemory();
}

void Ray::freeMemory()
{
  delete rayOrigin;
  delete rayDirection;
}

void Ray::set(Point const& point, Vector const& vector)
{
  *rayOrigin = point;
  *rayDirection = vector;
}

void Ray::setOrigin(Point const& point)
{
  *rayOrigin = point;
}

void Ray::setDirection(Vector const& vector)
{

  *rayDirection = vector;
}

Point Ray::origin() const
{
  return *rayOrigin;
}

Vector Ray::direction() const
{
  return *rayDirection;
}


Ray::Intersection Ray::intersection2D(Ray const& another, Point* intersection) const
/* Algorithm adapted from http://pastebin.com/f22ec3cf1
   http://www.gamedev.net/topic/518648-intersection-of-rays/ */
{
  double r, s, d;

  double x1 = origin().x(), y1 = origin().y(),
         x2 = origin().x() + direction().x(), y2 = origin().y() + direction().y(),
         x3 = another.origin().x(), y3 = another.origin().y(),
         x4 = another.origin().x() + another.direction().x(), y4 = another.origin().y() + another.direction().y();

  if (std::abs((y2 - y1) / (x2 - x1) - (y4 - y3) / (x4 - x3)) > libcity::EPSILON)
  /* Make sure the lines aren't parallel */
  {
    d = (((x2 - x1) * (y4 - y3)) - (y2 - y1) * (x4 - x3));
    if (d != 0)
    {
      r = (((y1 - y3) * (x4 - x3)) - (x1 - x3) * (y4 - y3)) / d;
      s = (((y1 - y3) * (x2 - x1)) - (x1 - x3) * (y2 - y1)) / d;
      if (r >= 0 || r >= -libcity::EPSILON) // Check with an EPSILON to count in double error
      {
        if (s >= 0 || s >= -libcity::EPSILON)
        {
          intersection->set(x1 +  r * (x2 - x1), y1 + r * (y2 - y1));
          return INTERSECTING;
        }
      }
    }
  }
  else
  {
    return PARALLEL;
  }
  return NONINTERSECTING;
}

Ray::Intersection Ray::intersection2D(Line const& another, Point* intersection) const
/* Algorithm adapted from http://pastebin.com/f22ec3cf1
   http://www.gamedev.net/topic/518648-intersection-of-rays/ */
{
  double r, s, d;

  double x1 = origin().x(), y1 = origin().y(),
         x2 = origin().x() + direction().x(), y2 = origin().y() + direction().y(),
         x3 = another.begining().x(), y3 = another.begining().y(),
         x4 = another.end().x(), y4 = another.end().y();

  if ((x2 - x1) == 0 && (x2 - x1) == (x4 - x3))
  {
    return PARALLEL;
  }

  if (std::abs((y2 - y1) / (x2 - x1) - (y4 - y3) / (x4 - x3)) > libcity::EPSILON)
  /* Make sure the lines aren't parallel */
  {
    d = (((x2 - x1) * (y4 - y3)) - (y2 - y1) * (x4 - x3));
    if (d != 0)
    {
      r = (((y1 - y3) * (x4 - x3)) - (x1 - x3) * (y4 - y3)) / d;
      s = (((y1 - y3) * (x2 - x1)) - (x1 - x3) * (y2 - y1)) / d;
      if (r >= 0 || r >= -libcity::EPSILON) // Check with an EPSILON to count in double error
      {
        intersection->set(x1 +  r * (x2 - x1), y1 + r * (y2 - y1));
        return INTERSECTING;
      }
    }
  }
  else
  {
    return PARALLEL;
  }
  return NONINTERSECTING;
}


std::string Ray::toString()
{
  return "Ray(" + rayOrigin->toString() + ", " + rayDirection->toString() + ")";
}
