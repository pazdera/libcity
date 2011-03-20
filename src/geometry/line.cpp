/**
 * This code is part of libcity library.
 *
 * @file geometry/line.cpp
 * @date 23.02.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @see geometry/line.h
 *
 */

#include "line.h"
#include "point.h"
#include "units.h"
#include "../debug.h"

#include <cmath>

Line::Line()
  : first(0), second(0)
{
  first = new Point(0,0,0);
  second      = new Point(0,0,0);
}

Line::Line(Point const& firstPoint, Point const& secondPoint)
  : first(0), second(0)
{
  first = new Point(firstPoint);
  second      = new Point(secondPoint);
}

Line::~Line()
{
  delete first;
  delete second;
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
  if ((point.x() - first->x()) * (second->y() - first->y()) -
      (point.y() - first->y()) * (second->x() - first->x()) == 0
     )
  /* Point is on the line */
  {
    double t = 0.0;
    if (first->x() != second->x())
    {
      t = (point.x() - first->x()) / (second->x() - first->x());
    }
    else if (first->y() != second->y())
    {
      t = (point.y() - first->y()) / (second->y() - first->y());
    }
    else
    {
      return (*first) == point;
    }
    return t >= 0 && t <= 1;
  }

  return false;
}

Line::Intersection Line::intersection2D(Line const& another, Point* intersection) const
// SOURCE: http://paulbourke.net/geometry/lineline2d/
{
  double denominator     = ((another.end().y() - another.begining().y())*(end().x() - begining().x())) -
                           ((another.end().x() - another.begining().x())*(end().y() - begining().y())),
         firstNumerator  = ((another.end().x() - another.begining().x())*(begining().y() - another.begining().y())) -
                           ((another.end().y() - another.begining().y())*(begining().x() - another.begining().x())),
         secondNumerator = ((end().x() - begining().x())*(begining().y() - another.begining().y())) -
                           ((end().y() - begining().y())*(begining().x() - another.begining().x()));

  if (denominator == 0.0)
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
      ub >= 0 && ub <= 1
     )
  {
    intersection->setX(begining().x() + ua*(end().x() - begining().x()));
    intersection->setY(begining().y() + ua*(end().y() - begining().y()));

    return INTERSECTING;
  }

  return NONINTERSECTING;
}

bool Line::operator==(Line const& another) const
{
  return (begining() == another.begining() && end() == another.end()) ||
         (begining() == another.end() && begining() == another.end());
}
