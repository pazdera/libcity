/**
 * This code is part of libcity library.
 *
 * @file streetgraph/rasterroadpattern.cpp
 * @date 17.03.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @see rasterroadpattern.h
 *
 */

#include "rasterroadpattern.h"

#include "../geometry/point.h"
#include "../geometry/vector.h"

RasterRoadPattern::RasterRoadPattern()
{}

RasterRoadPattern::~RasterRoadPattern()
{}

void RoadLSystem::turnLeft()
{
  Vector direction = cursor.getDirection();
  direction.rotateAroundZ(-90);

  cursor.setDirection(direction);
}

void RoadLSystem::turnRight()
{
  Vector direction = cursor.getDirection();
  direction.rotateAroundZ(90);

  cursor.setDirection(direction);
}