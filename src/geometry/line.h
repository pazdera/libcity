/**
 * This code is part of libcity library.
 *
 * @file geometry/line.h
 * @date 19.02.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @brief Representation of a line segment
 *
 * Also basic geometric operation with line are implemented
 * here.
 */

#ifndef _LINE_H_
#define _LINE_H_

class Point;

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

    void setBegining(Point const& point);
    void setEnd(Point const& point);

    Point begining() const;
    Point end() const;

    ~Line();

    double length() const;

    bool hasPoint2D(Point const& point) const;
    Intersection intersection2D(Line const& another, Point* intersection) const;

    bool operator==(Line const& another) const;

  private:
    Point *first;
    Point *second;
};

#endif
