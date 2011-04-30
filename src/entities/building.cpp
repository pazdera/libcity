/**
 * This code is part of libcity library.
 *
 * @file entities/building.cpp
 * @date 30.04.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @see building.h
 *
 */

#include "building.h"

#include "../debug.h"
#include "../geometry/units.h"
#include "../geometry/point.h"
#include "../geometry/polygon.h"
#include "../geometry/vector.h"
#include "../area/lot.h"
#include "../entities/urbanentity.h"


const Building::Type Building::SKY_SCRAPER = UrbanEntity::defineNewEntityType();

Building::Building()
{
  initialize();
}

Building::Building(Lot* parentAlottment)
  : UrbanEntity(parentAlottment)
{
  initialize();
}

void Building::initialize()
{}

Building::~Building()
{
}

Building::Building(Building const& source)
{
  
}

Building& Building::operator=(Building const& source)
{
  UrbanEntity::operator=(source);

  return *this;
}

void Building::generate()
{
  
}
