/**
 * This code is part of libcity library.
 *
 * @file area/lot.cpp
 * @date 26.04.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @see lot.h
 *
 */

#include "lot.h"

#include "../debug.h"
#include "../geometry/units.h"
#include "../geometry/point.h"
#include "../geometry/polygon.h"
#include "../geometry/vector.h"
#include "block.h"

Lot::Lot()
{
  initialize();
}

Lot::Lot(Block* parentBlock)
{
  initialize();
  setParent(parentBlock);
}

Lot::Lot(Lot const& source)
  : Area(source)
{
  initialize();
}

void Lot::initialize()
{
}

Lot& Lot::operator=(Lot const& source)
{
  Area::operator=(source);

  return *this;
}

Lot::~Lot()
{
  freeMemory();
}

void Lot::freeMemory()
{
}
