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

Line::Line()
  : begining(0), end(0)
{
  begining = new Point(0,0,0);
  end      = new Point(0,0,0);
}

Line::Line(Point first, Point second)
  : begining(0), end(0)
{
  begining = new Point(first);
  end      = new Point(second);
}

Line::~Line()
{
  delete begining;
  delete end;
}
