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

#include <cstdlib>

RasterRoadPattern::RasterRoadPattern()
{
  setAxiom("E");

  // Rules
  addRule('E', "[[-_E]+_E]_E");

  setInitialPosition(Point(0,0));
  setInitialDirection(Vector(0,1));
}

RasterRoadPattern::~RasterRoadPattern()
{}

double RasterRoadPattern::getTurnAngle()
{
  return (rand() % 80 + 10);
}
double RasterRoadPattern::getRoadSegmentLength()
{
  return (rand() % 100 + 50);
}