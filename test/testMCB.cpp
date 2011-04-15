/**
 * This code is part of libcity library.
 *
 * @file test/testMCB.cpp
 * @date 31.03.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @brief Unit test of MCB class
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
#include "../src/streetgraph/minimalcyclebasis.h"
#include "../src/streetgraph/rasterroadpattern.h"
#include "../src/geometry/polygon.h"
#include "../src/geometry/point.h"
#include "../src/debug.h"

SUITE(MCBClass)
{
  TEST(Basic)
  {
//     StreetGraph *sg = new StreetGraph();
// 
//     Polygon *constraints = new Polygon;
//     constraints->addVertex(Point(-100,100));
//     constraints->addVertex(Point(100,100));
//     constraints->addVertex(Point(100,-100));
//     constraints->addVertex(Point(-100,-100));
// 
// 
//     RasterRoadPattern* generator = new RasterRoadPattern;
//     generator->setTarget(sg);
//     generator->setAreaConstraints(constraints);
// 
//     generator->generateRoads(10);
// 
//     MinimalCycleBasis* graph = new MinimalCycleBasis(sg->intersections);
// 
//     std::list<Polygon> zones = graph->getMinimalCycles();
//     debug(zones.size());
  }
}