/**
 * This code is part of libcity library.
 *
 * @file geometry/linesegment.h
 * @date 19.02.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @brief Representation of a line segment
 *
 * Also basic geometric operation with line are implemented
 * here.
 */

#ifndef _LINESEGMENT_H_
#define _LINESEGMENT_H_

#include <string>

#include "line.h"

class Point;
class Vector;

class LineSegment : public Line
{
  public:
    LineSegment();
    LineSegment(Point const& firstPoint, Point const& secondPoint);
    LineSegment(Point const& point, Vector const& vector);

    LineSegment(LineSegment const& source); /**< Own copy constructor is neccessary */
    LineSegment& operator=(LineSegment const& source); /**< Own assignment operator is neccessary */

    ~LineSegment();

    double length() const;

    bool hasPoint2D(Point const& point) const;
    Intersection intersection2D(LineSegment const& another, Point* intersection) const;
    double distance(Point const& point) const;
    Point nearestPoint(Point const& point) const;

    std::string toString();

    bool operator==(LineSegment const& another) const;
};

#endif
