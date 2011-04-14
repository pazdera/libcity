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

    /* Static factories of different configurations */
    static Random doubleValue(double lower, double higher);
    static Random integerValue(int lower, int higher);
    static Random boolValue(double chance);

    Random();
    Random(double ownSeed);
    ~Random();

    double generateDouble(double lower, double higher);
    int generateInteger(int lower, int higher);
    bool generateBool(double chance);

    double generate();

  private:
    double base();

    bool   useOwnSeed;
    unsigned int state;

    /* For value objects */
    enum values
    {
      NONE,
      DOUBLE_VALUE,
      INTEGER_VALUE,
      BOOL_VALUE
    };
    values configuration;
    double lowerBound;
    double higherBound;
    double probability;
};

#endif