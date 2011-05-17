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
  addRule('E', "[[-_E]+_E]_E");
//   addRule('E', "[[-_E]+_E]");
//   addRule('E', "_E");

  setInitialPosition(Point(0,0));
  setInitialDirection(Vector(1,0));

  setTurnAngle(90, 90);
}

RasterRoadPattern::~RasterRoadPattern()
{}

// double RasterRoadPattern::getTurnAngle()
// {
//   return 90;
// }
// double RasterRoadPattern::getRoadSegmentLength()
// {
//   return Random::doubleValue(50,70).generate();
// }