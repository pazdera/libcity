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
{
  setAxiom("E");

  // Rules
  addRule('E', "[[-_E]+_E]_E");
}

RasterRoadPattern::~RasterRoadPattern()
{}

double RasterRoadPattern::getTurnAngle()
{
  return 90;
}
double RasterRoadPattern::getRoadSegmentLength()
{
  return 100;
}