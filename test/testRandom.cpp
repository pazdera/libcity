/**
 * This code is part of libcity library.
 *
 * @file test/testStreetGraph.h
 * @date 23.03.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @brief Unit test of Random class
 *
 * Unit tests require UnitTest++ framework! See README
 * for more informations.
 */

/* Include UnitTest++ headers */
#include <UnitTest++.h>

// Includes
#include <iostream>
#include <string>
#include <stdexcept>

// Tested modules
#include "../src/random.h"
#include "../src/debug.h"

SUITE(RandomClass)
{
  TEST(OwnSeed)
  {
    Random g1(libcity::RANDOM_SEED), g2(libcity::RANDOM_SEED), generator;

    generator.doubleValue(0,100);
    CHECK_EQUAL(g1.doubleValue(0,100), g2.doubleValue(0,100));
    CHECK_EQUAL(generator.doubleValue(0,100), g2.doubleValue(0,100));
    CHECK_EQUAL(generator.doubleValue(0,100), g2.doubleValue(0,100));

    g1.doubleValue(0,100);
    g1.doubleValue(0,100);
    CHECK_EQUAL(g1.doubleValue(0,100), g2.doubleValue(0,100));
  }

  TEST(doubleValue)
  {
    Random generator;
    CHECK(generator.doubleValue(0, 1) >= 0);
    CHECK(generator.doubleValue(0, 1) <= 1);

    CHECK(generator.doubleValue(1, 0) >= 0);
    CHECK(generator.doubleValue(1, 0) <= 1);

    CHECK(generator.doubleValue(2,2) == 2);
  }

  TEST(Flag)
  {
    Random generator;

    generator.flag(0.5);

    CHECK_EQUAL(1, generator.flag(1));
    CHECK_EQUAL(1, generator.flag(1));
    CHECK_EQUAL(1, generator.flag(1));
    CHECK_EQUAL(1, generator.flag(1));
    CHECK_EQUAL(1, generator.flag(1));
    CHECK_EQUAL(1, generator.flag(1));
    CHECK_EQUAL(1, generator.flag(1));
    CHECK_EQUAL(1, generator.flag(1));
    CHECK_EQUAL(1, generator.flag(1));
    CHECK_EQUAL(1, generator.flag(1));
    CHECK_EQUAL(1, generator.flag(1));
    CHECK_EQUAL(1, generator.flag(1));
    CHECK_EQUAL(1, generator.flag(1));
    CHECK_EQUAL(1, generator.flag(1));
    CHECK_EQUAL(1, generator.flag(1));
    CHECK_EQUAL(1, generator.flag(1));
    CHECK_EQUAL(1, generator.flag(1));
    CHECK_EQUAL(1, generator.flag(1));

    CHECK_EQUAL(0, generator.flag(0));
    CHECK_EQUAL(0, generator.flag(0));
    CHECK_EQUAL(0, generator.flag(0));
    CHECK_EQUAL(0, generator.flag(0));
    CHECK_EQUAL(0, generator.flag(0));
    CHECK_EQUAL(0, generator.flag(0));
    CHECK_EQUAL(0, generator.flag(0));
    CHECK_EQUAL(0, generator.flag(0));
    CHECK_EQUAL(0, generator.flag(0));
    CHECK_EQUAL(0, generator.flag(0));
    CHECK_EQUAL(0, generator.flag(0));
    CHECK_EQUAL(0, generator.flag(0));
    CHECK_EQUAL(0, generator.flag(0));
    CHECK_EQUAL(0, generator.flag(0));
    CHECK_EQUAL(0, generator.flag(0));
    CHECK_EQUAL(0, generator.flag(0));
    CHECK_EQUAL(0, generator.flag(0));
    CHECK_EQUAL(0, generator.flag(0));
  }
}