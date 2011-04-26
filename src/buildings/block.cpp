/**
 * This code is part of libcity library.
 *
 * @file buildings/block.cpp
 * @date 25.04.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @see block.h
 *
 */

#include "block.h"

#include "../debug.h"
#include "../geometry/units.h"
#include "../geometry/point.h"
#include "../geometry/polygon.h"
#include "../geometry/vector.h"
#include "../streetgraph/zone.h"

Block::Block()
{
  initialize();
}

Block::Block(Zone* parentZone)
{
  initialize();
  associatedZone = parentZone;
}

Block::Block(Zone* parentZone, Polygon const& border)
{
  initialize();
  associatedZone = parentZone;
  *constraints = border;
}

Block::Block(Block const& source)
{
  initialize();

  associatedZone = source.associatedZone;
  *constraints = *(source.constraints);
}

void Block::initialize()
{
  constraints = new Polygon();
}

Block& Block::operator=(Block const& source)
{
  reset();

  associatedZone = source.associatedZone;
  *constraints = *(source.constraints);

  return *this;
}

void Block::reset()
{
  constraints->clear();
}

Block::~Block()
{
  freeMemory();
}

void Block::freeMemory()
{
  delete constraints;
}

Polygon Block::areaConstraints()
{
  return *constraints;
}

void Block::setAreaConstraints(Polygon const& area)
{
  *constraints = area;
}

void Block::setZone(Zone* zone)
{
  associatedZone = zone;
}