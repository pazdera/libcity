/**
 * This code is part of libcity library.
 *
 * @file entities/urbanentity.cpp
 * @date 30.04.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @see urbanentity.h
 *
 */

#include "urbanentity.h"

#include "../debug.h"
#include "../geometry/units.h"
#include "../geometry/point.h"
#include "../geometry/polygon.h"
#include "../geometry/vector.h"
#include "../area/lot.h"


unsigned int UrbanEntity::numberOfDefinedEntityTypes = 1000;

UrbanEntity::Type UrbanEntity::defineNewEntityType()
{
  numberOfDefinedEntityTypes++;
  return numberOfDefinedEntityTypes;
}

UrbanEntity::UrbanEntity()
{}

UrbanEntity::UrbanEntity(Lot* parentAlottment)
{
  setLot(parentAlottment);
}

UrbanEntity::~UrbanEntity()
{
}

UrbanEntity::Type UrbanEntity::type()
{
  return entityType;
}

void UrbanEntity::setType(Type const& typeId)
{
  entityType = typeId;
}


Lot* UrbanEntity::lot()
{
  return parentLot;
}

void UrbanEntity::setLot(Lot* parentAlottment)
{
  parentLot = parentAlottment;
}
