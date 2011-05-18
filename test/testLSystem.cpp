/**
 * This code is part of libcity library.
 *
 * @file test/testLSystem.cpp
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
#include <stdexcept>

// Tested modules
#include "../src/lsystem/lsystem.h"

SUITE(LSystemClass)
{
  TEST(Algae)
  {
    LSystem *lsystem = new LSystem();
    lsystem->setAlphabet("AB");
    lsystem->setAxiom("A");

    lsystem->addRule('A', "AB");
    lsystem->addRule('B', "A");

    lsystem->doIterations(1);
    CHECK_EQUAL(lsystem->getProducedString(), "AB");

    lsystem->doIterations(1);
    CHECK_EQUAL(lsystem->getProducedString(), "ABA");

    lsystem->doIterations(1);
    CHECK_EQUAL(lsystem->getProducedString(), "ABAAB");

    lsystem->doIterations(1);
    CHECK_EQUAL(lsystem->getProducedString(), "ABAABABA");

    lsystem->doIterations(1);
    CHECK_EQUAL(lsystem->getProducedString(), "ABAABABAABAAB");

    lsystem->doIterations(1);
    CHECK_EQUAL(lsystem->getProducedString(), "ABAABABAABAABABAABABA");

    lsystem->doIterations(1);
    CHECK_EQUAL(lsystem->getProducedString(), "ABAABABAABAABABAABABAABAABABAABAAB");

    delete lsystem;
  }

  TEST(Fibonacci)
  {
    LSystem *lsystem = new LSystem();
    lsystem->setAlphabet("AB");
    lsystem->setAxiom("A");

    lsystem->addRule('A', "B");
    lsystem->addRule('B', "AB");

    lsystem->doIterations(7);
    CHECK_EQUAL(lsystem->getProducedString(), "BABABBABABBABBABABBAB");

    delete lsystem;
  }

  TEST(Misc)
  {
    LSystem *lsystem = new LSystem();
    CHECK_EQUAL(lsystem->getProducedString(), "");

    /* Alphabet not set */
    //lsystem->setAxiom("A"); // Should throw something
    //CHECK_EQUAL(lsystem->getProducedString(), "");

    lsystem->addToAlphabet("AB");
    lsystem->setAxiom("A");
    CHECK_EQUAL(lsystem->getProducedString(), "A");

    /* Is already in alphabet */
    lsystem->addToAlphabet("A");

    /* No rules set, should do nothing */
    lsystem->setAxiom("AB");
    lsystem->doIterations(10);
    CHECK_EQUAL(lsystem->getProducedString(), "AB");

    delete lsystem;
  }
}