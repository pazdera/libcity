/**
 * This code is part of libcity library.
 *
 * @file test/testStreetGraph.h
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

SUITE(StreetGraphClass)
{
  TEST(Empty)
  {
    StreetGraph *sg = new StreetGraph();

    Polygon *constraints = new Polygon;
    sg->setAreaConstraints(constraints);


  }
}