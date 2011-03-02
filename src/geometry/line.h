/**
 * This code is part of libcity library.
 *
 * @file geometry/line.h
 * @date 19.02.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @brief Representation of a line segment
 *
 */

#ifndef _LINE_H_
#define _LINE_H_

class Point;

class Line
{
  public:
    Line();
    Line(Point &first, Point &second);

    ~Line();

  private:
    Point *begining;
    Point *end;
};

#endif
