/**
 * This code is part of libcity library.
 *
 * @file vector.class.test.h
 * @date 13.03.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @brief Unit test of LSystem class
 *
 * Unit tests require UnitTest++ framework! See README
 * for more informations.
 */

/* Include UnitTest++ headers */
#include <UnitTest++.h>

// Includes
#include <iostream>
#include <string>

// Tested modules
#include "../src/lsystem/lsystem.h"

SUITE(LSystemClass)
{
  TEST(Algae)
  {
    LSystem lsystem;
    lsystem.setAlphabet("AB");
    lsystem.setAxiom("A");

    lsystem.addRule('A', "AB");
    lsystem.addRule('B', "A");

    lsystem.doIterations(1);
    CHECK_EQUAL(lsystem.getProducedString(), "AB");

    lsystem.doIterations(1);
    CHECK_EQUAL(lsystem.getProducedString(), "ABA");

    lsystem.doIterations(1);
    CHECK_EQUAL(lsystem.getProducedString(), "ABAAB");

    lsystem.doIterations(1);
    CHECK_EQUAL(lsystem.getProducedString(), "ABAABABA");

    lsystem.doIterations(1);
    CHECK_EQUAL(lsystem.getProducedString(), "ABAABABAABAAB");

    lsystem.doIterations(1);
    CHECK_EQUAL(lsystem.getProducedString(), "ABAABABAABAABABAABABA");

    lsystem.doIterations(1);
    CHECK_EQUAL(lsystem.getProducedString(), "ABAABABAABAABABAABABAABAABABAABAAB");
  }

  TEST(Fibonacci)
  {
    LSystem lsystem;
    lsystem.setAlphabet("AB");
    lsystem.setAxiom("A");

    lsystem.addRule('A', "B");
    lsystem.addRule('B', "AB");

    lsystem.doIterations(7);
    CHECK_EQUAL(lsystem.getProducedString(), "BABABBABABBABBABABBAB");
  }

  TEST(Misc)
  {
    LSystem lsystem;
    CHECK_EQUAL(lsystem.getProducedString(), "");

    /* Alphabet not set */
//     lsystem.setAxiom("A");
//     CHECK_EQUAL(lsystem.getProducedString(), "");
  }
}