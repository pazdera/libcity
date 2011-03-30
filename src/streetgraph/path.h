/**
 * This code is part of libcity library.
 *
 * @file streetgraph/path.h
 * @date 23.03.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @brief Path representation
 *
 * Says what path takes the road between two intersections.
 */

#ifndef _PATH_H_
#define _PATH_H_

#include <string>

class Line;
class Point;
class Vector;
class Polygon;

class Path
{
  public:
    Path();
    Path(Line const& line);

    Path(Path const& source);
    Path& operator=(Path const& source);

    ~Path();

    Point begining() const;
    Point end() const;

    void setBegining(Point const& begining);
    void setEnd(Point const& end);

    void trimOverlapingPart(Polygon const& boundaries);
    bool isInside(Polygon const& certainArea) const;

    bool goesThrough(Point const& certainPoint);
    bool crosses(Path const& anotherPath, Point* intersection);

    Point nearestPoint(Point const& point);
    double distance(Point const& point);

    void shorten(Point const& newBegining, Point const& newEnd);

    void snap(Point const& intersection);
    void snap(Path const& road);

    std::string toString();
  private:
   Line *representation;
};


#endif
