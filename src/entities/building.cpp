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
#include "../geometry/shape.h"
#include "../area/lot.h"
#include "../entities/urbanentity.h"


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
{
  Polygon area = parentLot->areaConstraints();
  boundingBox = new Shape();
  boundingBox->setBase(area);
  boundingBox->setHeight(0);

  addToAlphabet("{}");

  setInitialPosition(area.centroid());
  setInitialDirection(Vector(0,0,1));
}

void Building::interpretSymbol(char symbol)
{
  switch (symbol)
  {
    case '{':
      pushBoundingBox();
      break;
    case '}':
      popBoundingBox();
      break;
    default:
      /* Try to interpret symbols defined in parent. */
      GraphicLSystem::interpretSymbol(symbol);
      break;
  }
}

Building::~Building()
{
  freeMemory();
}

void Building::freeMemory()
{
  delete boundingBox;
}

Building::Building(Building const& source)
  : UrbanEntity(source)
{
  initialize();
  *boundingBox = *(source.boundingBox);
}

Building& Building::operator=(Building const& source)
{
  UrbanEntity::operator=(source);

  *boundingBox = *(source.boundingBox);

  return *this;
}
/*
void Building::draw()
{
  
}*/

double Building::maxHeight()
{
  return boundingBox->height();
}

void Building::setMaxHeight(double maxHeight)
{
  boundingBox->setHeight(maxHeight);
}

void Building::pushBoundingBox()
{
  boundingBoxStack.push_back(boundingBox);
}

void Building::popBoundingBox()
{
  assert(boundingBoxStack.size() > 0);

  // FIXME produces leaks
  boundingBox = boundingBoxStack.back();
  //delete boundingBoxStack.back();
  boundingBoxStack.pop_back();
}