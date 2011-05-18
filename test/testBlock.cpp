/**
 * This code is part of libcity library.
 *
 * @file test/testBlock.cpp
 * @date 25.04.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @brief Unit test of Block class
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
#include "../src/area/block.h"
#include "../src/geometry/vector.h"
#include "../src/geometry/point.h"
#include "../src/geometry/polygon.h"
#include "../src/geometry/linesegment.h"
#include "../src/debug.h"

SUITE(Block)
{
  TEST(SubdivisionAlgorithm)
  {
    Polygon p;
    p.addVertex(Point(0,0));
    p.addVertex(Point(200,0));
    p.addVertex(Point(200,200));
    p.addVertex(Point(0,200));

    Block b(0, p);

    b.createLots(50,50,0.0);

    std::list<Lot*> lots = b.getLots();
  }
}