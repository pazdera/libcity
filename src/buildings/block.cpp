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

Block::Block()
{
}

Block::Block(Polygon const& boundaries)
{
}

Block::Block(Block const& source)
{
  
}

Block& Block::operator=(Block const& source)
{
  return *this;
}

Block::~Block()
{

}
