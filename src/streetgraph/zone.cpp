/**
 * This code is part of libcity library.
 *
 * @file streetgraph/zone.cpp
 * @date 05.04.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @see streetgraph/zone.h
 *
 */

#include "zone.h"

#include "streetgraph.h"
#include "../geometry/polygon.h"
#include "../lsystem/roadlsystem.h"

Zone::Zone(StreetGraph* streets)
{
  initialize();
  associatedStreetGraph = streets;
}

void Zone::initialize()
{
  associatedStreetGraph = 0;
  roadGenerator = 0;
  constraints = new Polygon();
}

Zone::~Zone()
{
  freeMemory();
}

void Zone::freeMemory()
{
  freeRoadGenerator();
  delete constraints;
}

void Zone::freeRoadGenerator()
{
  if (roadGenerator != 0)
  {
    delete roadGenerator;
  }
}

Zone::Zone(Zone const& source)
{
  initialize();
  associatedStreetGraph = source.associatedStreetGraph;
  *constraints = *(source.constraints);
  roadGenerator = source.roadGenerator;
}

Zone& Zone::operator=(Zone const& source)
{
  associatedStreetGraph = source.associatedStreetGraph;
  *constraints = *(source.constraints);

  roadGenerator = source.roadGenerator;

  return *this;
}

void Zone::setRoadGenerator(RoadLSystem* generator)
{
  roadGenerator = generator;
}

void Zone::setAreaConstraints(Polygon const& area)
{
  *constraints = area;
}

Polygon Zone::areaConstraints()
{
  return *constraints;
}

void Zone::setStreetGraph(StreetGraph* streets)
{
  associatedStreetGraph = streets;
}