/**
 * This code is part of libcity library.
 *
 * @file random.h
 * @date 23.03.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @brief Random number generator class.
 *
 */

#ifndef _RANDOM_H_
#define _RANDOM_H_

namespace libcity
{
  const unsigned int RANDOM_SEED = 5;
}

class Random
{
  private:
    static unsigned int seed;

  public:
    Random();
    Random(double ownSeed);
    ~Random();

    double generate(double lowerBound, double higherBound);

    bool flag(double probability);

  private:
    double base();

    bool   useOwnSeed;
    unsigned int state;
};

#endif