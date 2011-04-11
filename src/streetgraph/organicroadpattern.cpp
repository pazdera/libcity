/**
 * This code is part of libcity library.
 *
 * @file streetgraph/organicroadpattern.cpp
 * @date 11.04.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @see rasterroadpattern.h
 *
 */

#include "organicroadpattern.h"

#include "../geometry/point.h"
#include "../geometry/vector.h"

#include "../random.h"

OrganicRoadPattern::OrganicRoadPattern()
  : RoadLSystem()
{
  setAxiom("E");

  // Rules
  addRule('E', "[[-_E]+_E]_E");
//   addRule('E', "[[-_E]+_E]");
//   addRule('E', "_E");

  setInitialPosition(Point(0,0));
  setInitialDirection(Vector(1,0));
}

OrganicRoadPattern::~OrganicRoadPattern()
{}

double OrganicRoadPattern::getTurnAngle()
{
  Random generator;

  return (generator.doubleValue(60,90));
}
double OrganicRoadPattern::getRoadSegmentLength()
{
  Random generator;

  return generator.doubleValue(50,70);
}