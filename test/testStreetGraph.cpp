/**
 * This code is part of libcity library.
 *
 * @file test/testStreetGraph.cpp
 * @date 19.03.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @brief Unit test of StreetGraph class
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
#include "../src/streetgraph/streetgraph.h"
#include "../src/streetgraph/rasterroadpattern.h"
#include "../src/geometry/polygon.h"
#include "../src/geometry/point.h"
#include "../src/geometry/linesegment.h"
#include "../src/streetgraph/path.h"

SUITE(StreetGraphClass)
{
  TEST(Empty)
  {
    StreetGraph *sg = new StreetGraph();
/*
    sg->addRoad(Path(LineSegment(Point(-3000, -2509.3, 0), Point(-3000, -2244.59, 0))));
    sg->addRoad(Path(LineSegment(Point(-3000, 837.305, 0), Point(-3000, -2509.3, 0))));*/
  }
}