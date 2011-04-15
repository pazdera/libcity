/**
 * This code is part of libcity library.
 *
 * @file test/testlsystem.cpp
 * @date 22.03.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @brief Unit test of RasterRoadPattern class
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
#include "../src/streetgraph/rasterroadpattern.h"
#include "../src/geometry/line.h"
#include "../src/streetgraph/path.h"
#include "../src/streetgraph/road.h"

#include "../src/debug.h"

SUITE(RasterRoadPatternClass)
{
  TEST(Basic)
  {
    RasterRoadPattern* rp = new RasterRoadPattern();
    Path roadSegment;
/*
    roadSegment = rp->getNextIdealRoadSegment();
    debug(roadSegment.toString());

    roadSegment = rp->getNextIdealRoadSegment();
    debug(roadSegment.toString());*/

    delete rp;
  }
}