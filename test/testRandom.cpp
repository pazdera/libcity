/**
 * This code is part of libcity library.
 *
 * @file test/testStreetGraph.cpp
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

    generator.generateDouble(0,100);
    CHECK_EQUAL(g1.generateDouble(0,100), g2.generateDouble(0,100));
    CHECK_EQUAL(generator.generateDouble(0,100), g2.generateDouble(0,100));
    CHECK_EQUAL(generator.generateDouble(0,100), g2.generateDouble(0,100));

    g1.generateDouble(0,100);
    g1.generateDouble(0,100);
    CHECK_EQUAL(g1.generateDouble(0,100), g2.generateDouble(0,100));
  }

  TEST(generateDouble)
  {
    Random generator;
    CHECK(generator.generateDouble(0, 1) >= 0);
    CHECK(generator.generateDouble(0, 1) <= 1);

    CHECK(generator.generateDouble(1, 0) >= 0);
    CHECK(generator.generateDouble(1, 0) <= 1);

    CHECK(generator.generateDouble(2,2) == 2);
  }

  TEST(generateBool)
  {
    Random generator;

    generator.generateBool(0.5);

    CHECK_EQUAL(1, generator.generateBool(1));
    CHECK_EQUAL(1, generator.generateBool(1));
    CHECK_EQUAL(1, generator.generateBool(1));
    CHECK_EQUAL(1, generator.generateBool(1));
    CHECK_EQUAL(1, generator.generateBool(1));
    CHECK_EQUAL(1, generator.generateBool(1));
    CHECK_EQUAL(1, generator.generateBool(1));
    CHECK_EQUAL(1, generator.generateBool(1));
    CHECK_EQUAL(1, generator.generateBool(1));
    CHECK_EQUAL(1, generator.generateBool(1));
    CHECK_EQUAL(1, generator.generateBool(1));
    CHECK_EQUAL(1, generator.generateBool(1));
    CHECK_EQUAL(1, generator.generateBool(1));
    CHECK_EQUAL(1, generator.generateBool(1));
    CHECK_EQUAL(1, generator.generateBool(1));
    CHECK_EQUAL(1, generator.generateBool(1));
    CHECK_EQUAL(1, generator.generateBool(1));
    CHECK_EQUAL(1, generator.generateBool(1));

    CHECK_EQUAL(0, generator.generateBool(0));
    CHECK_EQUAL(0, generator.generateBool(0));
    CHECK_EQUAL(0, generator.generateBool(0));
    CHECK_EQUAL(0, generator.generateBool(0));
    CHECK_EQUAL(0, generator.generateBool(0));
    CHECK_EQUAL(0, generator.generateBool(0));
    CHECK_EQUAL(0, generator.generateBool(0));
    CHECK_EQUAL(0, generator.generateBool(0));
    CHECK_EQUAL(0, generator.generateBool(0));
    CHECK_EQUAL(0, generator.generateBool(0));
    CHECK_EQUAL(0, generator.generateBool(0));
    CHECK_EQUAL(0, generator.generateBool(0));
    CHECK_EQUAL(0, generator.generateBool(0));
    CHECK_EQUAL(0, generator.generateBool(0));
    CHECK_EQUAL(0, generator.generateBool(0));
    CHECK_EQUAL(0, generator.generateBool(0));
    CHECK_EQUAL(0, generator.generateBool(0));
    CHECK_EQUAL(0, generator.generateBool(0));
  }
}