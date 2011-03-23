/**
 * This code is part of libcity library.
 *
 * @file random.cpp
 * @date 23.03.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @see random.h
 *
 */

#include "random.h"

#include <cstdlib>
#include <limits.h>

unsigned int Random::seed = libcity::RANDOM_SEED;

Random::Random()
  : useOwnSeed(false)
{
  state = seed;
}

Random::Random(double ownSeed)
  : useOwnSeed(true)
{
  state = ownSeed;
}

Random::~Random()
{}

double Random::generate(double lowerBound, double higherBound)
{
  double temporary;
  if (lowerBound > higherBound)
  {
    temporary   = lowerBound;
    lowerBound  = higherBound;
    higherBound = temporary;
  }

  return base() * (higherBound - lowerBound) + lowerBound;
}

bool Random::flag(double probability)
{
  return generate(0, 1) < probability;
}

int Random::base()
{
  state = 1103515245*state + 12345;

  if (!useOwnSeed)
  {
    seed = state;
  }

  return state / (static_cast<double>(UINT_MAX) + 1.0);
}
