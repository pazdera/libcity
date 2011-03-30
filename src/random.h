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
    static void setSeed(int newSeed);

    Random();
    Random(double ownSeed);
    ~Random();

    double doubleValue(double lowerBound, double higherBound);
    int integerValue(int lowerBound, int higherBound);

    bool flag(double probability);

  private:
    double base();

    bool   useOwnSeed;
    unsigned int state;
};

#endif