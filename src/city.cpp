/**
 * This code is part of libcity library.
 *
 * @file city.cpp
 * @date 07.03.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @see city.h
 *
 */

#include "city.h"

#include "streetgraph/streetgraph.h"
#include "streetgraph/zone.h"

City::City()
{
  initialize();
}

City::~City()
{
  freeMemory();
}

void City::initialize()
{
  map = new StreetGraph;
  zones = new std::list<Zone*>;
}
void City::freeMemory()
{
  delete map;
  delete zones;
}

void City::generate()
{
  createPrimaryRoadNetwork();
  createZones();
  createSecondaryRoadNetwork();
  createBlocks();
  createBuildings();
}

void City::draw()
{
  drawRoadNetwork();
  drawBuildings();
}
