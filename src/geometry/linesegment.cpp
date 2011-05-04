/**
 * This code is part of libcity library.
 *
 * @file geometry/linesegment.cpp
 * @date 23.02.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @see geometry/linesegment.h
 *
 */

#include "linesegment.h"
#include "point.h"
#include "polygon.h"
#include "vector.h"
#include "units.h"
#include "../debug.h"

#include <cmath>

LineSegment::LineSegment()
  : Line()
{}

LineSegment::LineSegment(Point const& firstPoint, Point const& secondPoint)
  : Line(firstPoint, secondPoint)
{}

LineSegment::LineSegment(Point const& point, Vector const& vector)
  : Line(point, point + vector)
{}

LineSegment::LineSegment(LineSegment const& source)
  : Line(source)
{}

LineSegment& LineSegment::operator=(LineSegment const& source)
{
  *first  = source.begining();
  *second = source.end();
  return *this;
}

LineSegment::~LineSegment()
{}

bool LineSegment::hasPoint2D(Point const& point) const
{
  double lineTest = (point.x() - first->x()) * (second->y() - first->y()) -
                    (point.y() - first->y()) * (second->x() - first->x());
//   debug(std::abs(lineTest));
//   debug(toString());
//   debug(point.toString());
  if (std::abs(lineTest) < libcity::COORDINATES_EPSILON)
  /* Point is on the line */
  {
    double t = 0.0;
    if (std::abs(first->x() - second->x()) > libcity::COORDINATES_EPSILON) //(first->x() != second->x()) 
    {
      t = (point.x() - first->x()) / (second->x() - first->x());
      //debug(t);
      return t >= 0 && t <= 1;
    }
    else if (std::abs(first->y() - second->y()) > libcity::COORDINATES_EPSILON) //(first->y() != second->y())
    {
      t = (point.y() - first->y()) / (second->y() - first->y());
      //debug(t);
      return t >= 0 && t <= 1;
    }
    else
    {
      return (*first) == point;
    }
  }

  return false;
}

LineSegment::Intersection LineSegment::intersection2D(LineSegment const& another, Point* intersection) const
// SOURCE: http://paulbourke.net/geometry/lineline2d/
{
  double denominator     = ((another.end().y() - another.begining().y())*(end().x() - begining().x())) -
                           ((another.end().x() - another.begining().x())*(end().y() - begining().y())),
         firstNumerator  = ((another.end().x() - another.begining().x())*(begining().y() - another.begining().y())) -
                           ((another.end().y() - another.begining().y())*(begining().x() - another.begining().x())),
         secondNumerator = ((end().x() - begining().x())*(begining().y() - another.begining().y())) -
                           ((end().y() - begining().y())*(begining().x() - another.begining().x()));

  if (std::abs(denominator) < libcity::COORDINATES_EPSILON)
  /* If the denominator is 0, both lines have same direction vector */
  {
    if  (std::abs(firstNumerator) < libcity::COORDINATES_EPSILON &&
        std::abs(secondNumerator) < libcity::COORDINATES_EPSILON)
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
      ub >= 0 && ub <= 1
     )
  {
    intersection->setX(begining().x() + ua*(end().x() - begining().x()));
    intersection->setY(begining().y() + ua*(end().y() - begining().y()));

    return INTERSECTING;
  }

  return NONINTERSECTING;
}

LineSegment::Intersection LineSegment::intersection2D(Line const& another, Point* intersection) const
{
  float r, s, d;

  double x1 = begining().x(), y1 = begining().y(),
         x2 = end().x(), y2 = end().y(),
         x3 = another.begining().x(), y3 = another.begining().y(),
         x4 = another.end().x(), y4 = another.end().y();

  // Make sure the lines aren't parallel
  if (std::abs((y2 - y1) / (x2 - x1) - (y4 - y3) / (x4 - x3)) > libcity::EPSILON)
  {
    d = (((x2 - x1) * (y4 - y3)) - (y2 - y1) * (x4 - x3));
    if (d != 0)
    {
      r = (((y1 - y3) * (x4 - x3)) - (x1 - x3) * (y4 - y3)) / d;
      s = (((y1 - y3) * (x2 - x1)) - (x1 - x3) * (y2 - y1)) / d;
      if (r >= -libcity::EPSILON && r <= (1 + libcity::EPSILON))
      {
        intersection->set(x1 +  r * (x2 - x1), y1 + r * (y2 - y1));
        return LineSegment::INTERSECTING;
      }
    }
  }

  return LineSegment::NONINTERSECTING;
}


Point LineSegment::nearestPoint(Point const& point) const
{
  double parameter;
  Point orthogonalProjection;

  parameter = (second->x() - first->x())*(point.x() - first->x()) +
              (second->y() - first->y())*(point.y() - first->y()) +
              (second->z() - first->z())*(point.z() - first->z());

  parameter /= length()*length();

  if (parameter >= 0 && parameter <=1)
  {
    orthogonalProjection.setX((1 - parameter)*first->x() + second->x()*parameter);
    orthogonalProjection.setY((1 - parameter)*first->y() + second->y()*parameter);
    orthogonalProjection.setZ((1 - parameter)*first->z() + second->z()*parameter);

    return orthogonalProjection;
  }
  else
  {
    double distanceToFirst  = Vector(point, *first).length();
    double distanceToSecond = Vector(point, *second).length();

    if (distanceToFirst < distanceToSecond)
    {
      return *first;
    }
    else
    {
      return *second;
    }
  }
}

double LineSegment::distance(Point const& point) const
{
  Point closestPoint = nearestPoint(point);

  return Vector(closestPoint, point).length();
}

double LineSegment::length() const
{
  Vector directionVector(*first, *second);
  return directionVector.length();
}

bool LineSegment::operator==(LineSegment const& another) const
{
  return (begining() == another.begining() && end() == another.end()) ||
         (begining() == another.end() && end() == another.begining());
}

Vector LineSegment::normal() const
{
  Vector direction = *second - *first;

  return Vector(-direction.y(), direction.x());
}


std::string LineSegment::toString() const
{
  return "LineSegment(" + first->toString() + ", " + second->toString() + ")";
}
