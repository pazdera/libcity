/**
 * This code is part of libcity library.
 *
 * @file area/block.cpp
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
#include "zone.h"
#include "lot.h"

Block::Block()
{
  initialize();
}

Block::Block(Zone* parentZone)
{
  initialize();
  setParent(parentZone);
}

Block::Block(Zone* parentZone, Polygon const& border)
{
  initialize();
  setParent(parentZone);
  setAreaConstraints(border);
}

Block::Block(Block const& source)
  : Area(source)
{
  initialize();
}

void Block::initialize()
{
  lots.clear();
}

Block& Block::operator=(Block const& source)
{
  Area::operator=(source);

  return *this;
}

Block::~Block()
{
  freeMemory();
}

void Block::freeMemory()
{
  lots.clear();
}
