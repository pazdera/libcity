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

#include "../random.h"

RasterRoadPattern::RasterRoadPattern()
  : RoadLSystem()
{
  setAxiom("E");

  // Rules
  addRule('E', "[[-_E]+_E]__E");

  setInitialPosition(Point(0,0));
  setInitialDirection(Vector(1,0));
}

RasterRoadPattern::~RasterRoadPattern()
{}

double RasterRoadPattern::getTurnAngle()
{
  Random generator;
  return (generator.doubleValue(60,90));
}
double RasterRoadPattern::getRoadSegmentLength()
{
  Random generator;
//   if (generator.flag(0.3))
//   {
//     return 50;
//   }
// 
//   return 70;
  return generator.doubleValue(50,70);
}