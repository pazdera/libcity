/**
 * This code is part of libcity library.
 *
 * @file geometry/line.cpp
 * @date 19.04.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @see geometry/line.h
 *
 */

#include "line.h"
#include "point.h"
#include "polygon.h"
#include "vector.h"
#include "units.h"
#include "../debug.h"

#include <cmath>

Line::Line()
{
  first  = new Point(0,0,0);
  second = new Point(0,0,0);
}

Line::Line(Point const& firstPoint, Point const& secondPoint)
{
  first  = new Point(firstPoint);
  second = new Point(secondPoint);
}

Line::Line(Point const& point, Vector const& vector)
{
  first  = new Point(point);
  second = new Point(point + vector);
}

Line::Line(Line const& source)
{
  first  = new Point(source.begining());
  second = new Point(source.end());
}

Line& Line::operator=(Line const& source)
{
  *first  = source.begining();
  *second = source.end();
  return *this;
}

Line::~Line()
{
  delete first;
  delete second;
}

void Line::set(Point const& begining, Point const& end)
{
  setBegining(begining);
  setEnd(end);
}

void Line::setBegining(Point const& point)
{
  delete first;
  first = new Point(point);
}

void Line::setEnd(Point const& point)
{

  delete second;
  second = new Point(point);
}

Point Line::begining() const
{
  return *first;
}

Point Line::end() const
{
  return *second;
}

bool Line::hasPoint2D(Point const& point) const
{
  double lineTest = (point.x() - first->x()) * (second->y() - first->y()) -
                    (point.y() - first->y()) * (second->x() - first->x());
  if (std::abs(lineTest) < libcity::EPSILON)
  /* Point is on the line */
  {
    return true;
  }

  return false;
}

Line::Intersection Line::intersection2D(Line const& another, Point* intersection) const
// SOURCE: http://paulbourke.net/geometry/lineline2d/
{
  double denominator     = ((another.end().y() - another.begining().y())*(end().x() - begining().x())) -
                           ((another.end().x() - another.begining().x())*(end().y() - begining().y())),
         firstNumerator  = ((another.end().x() - another.begining().x())*(begining().y() - another.begining().y())) -
                           ((another.end().y() - another.begining().y())*(begining().x() - another.begining().x()));

  if (std::abs(denominator) <= 0.001) // WARNING: should be libcity::EPSILON
  /* If the denominator is 0, both lines have same direction vector */
  {
    // Lines are parallel thus nonintersecting
    return PARALLEL;
  }

  double ua = firstNumerator  / denominator;

  intersection->setX(begining().x() + ua*(end().x() - begining().x()));
  intersection->setY(begining().y() + ua*(end().y() - begining().y()));

  return INTERSECTING;
}


Point Line::nearestPoint(Point const& point) const
{
  double parameter;
  Point orthogonalProjection;

  parameter = (second->x() - first->x())*(point.x() - first->x()) +
              (second->y() - first->y())*(point.y() - first->y()) +
              (second->z() - first->z())*(point.z() - first->z());

  parameter /= Vector(*first, *second).length()*Vector(*first, *second).length();

  orthogonalProjection.setX((1 - parameter)*first->x() + second->x()*parameter);
  orthogonalProjection.setY((1 - parameter)*first->y() + second->y()*parameter);
  orthogonalProjection.setZ((1 - parameter)*first->z() + second->z()*parameter);

  return orthogonalProjection;
}

double Line::distance(Point const& point) const
{
  Point closestPoint = nearestPoint(point);

  return Vector(closestPoint, point).length();
}

bool Line::operator==(Line const& another) const
{
  return (begining() == another.begining() && end() == another.end()) ||
         (begining() == another.end() && end() == another.begining());
}

std::string Line::toString()
{
  return "Line(" + first->toString() + ", " + second->toString() + ")";
}
