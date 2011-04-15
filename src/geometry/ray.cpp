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
// SOURCE: http://paulbourke.net/geometry/lineline2d/
{
  double denominator     = ((another.end().y() - another.begining().y())*(end().x() - begining().x())) -
                           ((another.end().x() - another.begining().x())*(end().y() - begining().y())),
         firstNumerator  = ((another.end().x() - another.begining().x())*(begining().y() - another.begining().y())) -
                           ((another.end().y() - another.begining().y())*(begining().x() - another.begining().x())),
         secondNumerator = ((end().x() - begining().x())*(begining().y() - another.begining().y())) -
                           ((end().y() - begining().y())*(begining().x() - another.begining().x()));

  if (std::abs(denominator) < libcity::EPSILON)
  /* If the denominator is 0, both lines have same direction vector */
  {
    if  (std::abs(firstNumerator) < libcity::EPSILON &&
        std::abs(secondNumerator) < libcity::EPSILON)
    /* Lines are coincident. */
    {

    /* WARNING
     * Order of following checks is important
     * for the right functionality. */

      if (*this == another)
      /* Line segments are identical */
      {
        return IDENTICAL;
      }

      if (hasPoint2D(another.begining()) && hasPoint2D(another.end()))
      /* This line is containing another. */
      {
        return CONTAINING;
      }

      if (another.hasPoint2D(begining()) && another.hasPoint2D(end()))
      /* This line is contained in another. */
      {
        return CONTAINED;
      }

      if (!this->hasPoint2D(another.begining()) &&
          !this->hasPoint2D(another.end()))
      /* Line segments are subsequent. */
      {
        return NONINTERSECTING;
      }

      if (begining() == another.begining() ||
          begining() == another.end())
      /* Line segments touch just in one point. */
      {
        *intersection = begining();
        return INTERSECTING;
      }

      if (end() == another.end() ||
          end() == another.begining())
      /* Line segments touch just in one point. */
      {
        *intersection = end();
        return INTERSECTING;
      }

      /* Line segments overlap */
      return OVERLAPING;
    }

    // Lines are parallel thus nonintersecting
    return NONINTERSECTING;
  }

  double ua = firstNumerator  / denominator,
         ub = secondNumerator / denominator;

  if (ua >= 0 && ua <= 1 &&
      ub >= 0 && ub <= 1)
  {
    intersection->setX(begining().x() + ua*(end().x() - begining().x()));
    intersection->setY(begining().y() + ua*(end().y() - begining().y()));

    return INTERSECTING;
  }

  return NONINTERSECTING;
}


std::string Ray::toString()
{
  return "Ray(" + rayOrigin->toString() + ", " + rayDirection->toString() + ")";
}
