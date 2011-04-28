/**
 * This code is part of libcity library.
 *
 * @file test/testRegion.cpp
 * @date 28.04.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @brief Unit test of Region class
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
#include "../src/area/region.h"
#include "../src/geometry/polygon.h"
#include "../src/debug.h"

SUITE(RegionClass)
{
  TEST(InitializeFromPolygon)
  {
    Polygon p;
    p.addVertex(Point(0,0));
    p.addVertex(Point(10,0));
    p.addVertex(Point(10,10));
    p.addVertex(Point(0,10));

    Region r(p);
    Region::Edge* e = r.getFirstEdge();

    CHECK(Point(0,0)  == e->begining);
    CHECK(Point(10,0) == e->next->begining);
    CHECK(Point(0,10) == e->previous->begining);
  }

  TEST(InsertInitialize)
  {
    Region r;
    Region::Edge* current;
    Region::Edge* e;

    current = r.insert(0, Point(0,0));
    current = r.insert(current, Point(10,0));
    current = r.insert(current, Point(10,10));
    current = r.insert(current, Point(0,10));

    e = r.getFirstEdge();
    CHECK(Point(0,0)   == e->begining);
    CHECK(Point(10,0)  == e->next->begining);
    CHECK(Point(0,10)  == e->previous->begining);
    CHECK(Point(0,0)   == e->previous->next->begining);
    CHECK(Point(10,10) == e->previous->previous->begining);
  }

  TEST(LongestEdges)
  {
    Region r;
    Region::Edge* current;

    current = r.insert(0, Point(0,0));
    current = r.insert(current, Point(10,0));
    current->hasRoadAccess = true;
    current = r.insert(current, Point(10,10));
    current->hasRoadAccess = false;

    CHECK(Point(10,0) == r.getLongestEdgeWithRoadAccess()->begining);
    CHECK(Point(10,10) == r.getLongestEdgeWithoutRoadAccess()->begining);

    CHECK(r.hasRoadAccess());
  }
}