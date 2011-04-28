/**
 * This code is part of libcity library.
 *
 * @file geometry/line.h
 * @date 19.04.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @brief Representation of a line
 *
 * Also basic geometric operation with line are implemented
 * here.
 * 
 * @note This is not a line segment.
 */

#ifndef _LINE_H_
#define _LINE_H_

#include <string>

class Point;
class Vector;

class Line
{
  public:
    enum Intersection
    {
      INTERSECTING = 0,
      NONINTERSECTING,
      PARALLEL,
      IDENTICAL,
      CONTAINING,
      CONTAINED,
      OVERLAPING
    };

    Line();
    Line(Point const& firstPoint, Point const& secondPoint);
    Line(Point const& point, Vector const& vector);

    Line(Line const& source); /**< Own copy constructor is neccessary */
    Line& operator=(Line const& source); /**< Own assignment operator is neccessary */

    void set(Point const& begining, Point const& end);
    void setBegining(Point const& point);
    void setEnd(Point const& point);

    Point begining() const;
    Point end() const;

    virtual ~Line();

    virtual bool hasPoint2D(Point const& point) const;
    virtual Intersection intersection2D(Line const& another, Point* intersection) const;
    virtual double distance(Point const& point) const;
    virtual Point nearestPoint(Point const& point) const;

    virtual std::string toString();

    bool operator==(Line const& another) const;

  protected:
    Point *first;
    Point *second;
};

#endif
