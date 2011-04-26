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
#include "area/zone.h"
#include "geometry/polygon.h"

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
  area = new Polygon;
  map = new StreetGraph;
  zones = new std::list<Zone*>;
}
void City::freeMemory()
{
  delete map;
  delete zones;
  delete area;
}

void City::generate()
{
  createPrimaryRoadNetwork();
  createZones();
  createSecondaryRoadNetwork();
  createBlocks();
  createBuildings();
}

