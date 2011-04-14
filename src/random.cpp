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

#include "debug.h"

#include <cstdlib>
#include <limits.h>

unsigned int Random::seed = libcity::RANDOM_SEED;

void Random::setSeed(int newSeed)
{
  Random::seed = newSeed;
}

Random::Random()
  : useOwnSeed(false), configuration(NONE)
{
  state = seed;
}

Random::Random(double ownSeed)
  : useOwnSeed(true), configuration(NONE)
{
  state = ownSeed;
}

Random::~Random()
{}

double Random::generateDouble(double lower, double higher)
{
  double temporary;
  if (lower > higher)
  {
    temporary   = lower;
    lower  = higher;
    higher = temporary;
  }

  return base() * (higher - lower) + lower;
}

int Random::generateInteger(int lower, int higher)
{
  int temporary;
  if (lower > higher)
  {
    temporary   = lower;
    lower  = higher;
    higher = temporary;
  }

  return base() * (higher + 1 - lower) + lower;
}

bool Random::generateBool(double chance)
{
  return generateDouble(0, 1) < chance;
}

double Random::base()
{
  state = 1103515245*state + 12345;

  if (!useOwnSeed)
  {
    seed = state;
  }

  return state / (static_cast<double>(UINT_MAX) + 1.0);
}

double Random::generate()
{
  switch (configuration)
  {
    case NONE:
      // FIXME exception
      return 0;
    case DOUBLE_VALUE:
      return generateDouble(lowerBound, higherBound);
    case INTEGER_VALUE:
      return generateInteger(lowerBound, higherBound);
    case BOOL_VALUE:
      return generateBool(probability);
  }
}


Random Random::doubleValue(double lower, double higher)
{
  Random generator;

  generator.configuration = DOUBLE_VALUE;
  generator.lowerBound = lower;
  generator.higherBound = higher;

  return generator;
}

Random Random::integerValue(int lower, int higher)
{
  Random generator;

  generator.configuration = INTEGER_VALUE;
  generator.lowerBound = lower;
  generator.higherBound = higher;

  return generator;
}

Random Random::boolValue(double chance)
{
  Random generator;

  generator.configuration = BOOL_VALUE;
  generator.probability = chance;

  return generator;
}
