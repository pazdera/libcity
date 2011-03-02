/**
 * This code is part of libcity library.
 *
 * @file geometry/point.cpp
 * @date 19.02.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @see geometry/point.h
 *
 */

#include "point.h"

Point::Point()
  : xPosition(0), yPosition(0), zPosition(0)
{}

Point::Point(int x, int y)
  : xPosition(x), yPosition(y), zPosition(0)
{}

Point::Point(int x, int y, int z)
  : xPosition(x), yPosition(y), zPosition(z)
{}

Point::~Point()
{}