/**
 * This code is part of libcity library.
 *
 * @file test/testGraphicLSystem.h
 * @date 13.03.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @brief Unit test of GraphicLSystem class
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
#include "../src/lsystem/graphiclsystem.h"

SUITE(GraphicLSystemClass)
{
  TEST(Access)
  {
    GraphicLSystem *gls = new GraphicLSystem;

    gls->setAxiom(".");
    gls->addRule('.', "-.");

    CHECK_EQUAL(gls->getProducedString(), ".");

    // No iterations done yet
    CHECK_EQUAL('.', gls->readNextSymbol());

    // First iteration
    CHECK_EQUAL('-', gls->readNextSymbol());
    CHECK_EQUAL('.', gls->readNextSymbol());

    // Second iteration
    CHECK_EQUAL('-', gls->readNextSymbol());
    CHECK_EQUAL('.', gls->readNextSymbol());

    // Third iteration
    CHECK_EQUAL('-', gls->readNextSymbol());
    CHECK_EQUAL('.', gls->readNextSymbol());

    delete gls;
  }

  TEST(Stack)
  {
    GraphicLSystem *gls = new GraphicLSystem;

    gls->setAxiom(".");
    gls->addRule('.', "[[-].]");

    CHECK_EQUAL(gls->getProducedString(), ".");

    // No iterations done yet
    CHECK_EQUAL('.', gls->readNextSymbol());

    // First
    CHECK_EQUAL('[', gls->readNextSymbol());
    CHECK_EQUAL('[', gls->readNextSymbol());
    CHECK_EQUAL('-', gls->readNextSymbol());
    CHECK_EQUAL(']', gls->readNextSymbol());
    CHECK_EQUAL('.', gls->readNextSymbol());
    CHECK_EQUAL(']', gls->readNextSymbol());

    // Second
    CHECK_EQUAL('[', gls->readNextSymbol());
    CHECK_EQUAL('[', gls->readNextSymbol());
    CHECK_EQUAL('-', gls->readNextSymbol());
    CHECK_EQUAL(']', gls->readNextSymbol());
    CHECK_EQUAL('.', gls->readNextSymbol());
    CHECK_EQUAL(']', gls->readNextSymbol());

    delete gls;
  }
}