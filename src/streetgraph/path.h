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

class Line;
class Point;
class Vector;

class Path
{
  public:
    Path();

    Path(Path const& source);
    Path& operator=(Path const& source);

    ~Path();

    Point begining() const;
    Point end() const;

    bool goesThrough(Point const& certainPoint);
    bool crosses(Path const& anotherPath);

    bool endsNear(Point const& certainPoint);
    bool endsNear(Path const& certainPath);

    void shorten(Point const& newBegining, Point const& newEnd);

    void snap(Point const& intersection);
    void snap(Path const& road);

  private:
   Line *representation;
};


#endif
