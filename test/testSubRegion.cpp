/**
 * This code is part of libcity library.
 *
 * @file test/testSubRegion.cpp
 * @date 28.04.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @brief Unit test of SubRegion class
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
#include "../src/area/subregion.h"
#include "../src/geometry/point.h"
#include "../src/geometry/polygon.h"
#include "../src/debug.h"

SUITE(SubRegionClass)
{
  TEST(InitializeFromPolygon)
  {
    Polygon p;
    p.addVertex(Point(0,0));
    p.addVertex(Point(10,0));
    p.addVertex(Point(10,10));
    p.addVertex(Point(0,10));

    SubRegion r(p);
    SubRegion::Edge* e = r.getFirstEdge();

    CHECK(Point(0,0)  == e->begining);
    CHECK(Point(10,0) == e->next->begining);
    CHECK(Point(0,10) == e->previous->begining);
  }

  TEST(InsertInitialize)
  {
    SubRegion r;
    SubRegion::Edge* current;
    SubRegion::Edge* e;

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
    SubRegion r;
    SubRegion::Edge* current;

    current = r.insert(0, Point(0,0));
    current = r.insert(current, Point(10,0));
    current->hasRoadAccess = true;
    current = r.insert(current, Point(10,10));
    current->hasRoadAccess = false;

    CHECK(Point(10,0) == r.getLongestEdgeWithRoadAccess()->begining);
    CHECK(Point(10,10) == r.getLongestEdgeWithoutRoadAccess()->begining);

    CHECK(r.hasRoadAccess());
  }

  TEST(ToPolygon)
  {
    SubRegion r;
    SubRegion::Edge* current;
    Polygon p;

    current = r.insert(0, Point(0,0));
    current = r.insert(current, Point(10,0));
    current = r.insert(current, Point(10,10));
    current = r.insert(current, Point(0,10));

    p = r.toPolygon();
    CHECK(Point(0,0)   == p.vertex(0));
    CHECK(Point(10,0)  == p.vertex(1));
    CHECK(Point(10,10) == p.vertex(2));
    CHECK(Point(0,10)  == p.vertex(3));
  }

  TEST(CopyConstructor)
  {
    SubRegion r;
    SubRegion::Edge* current;

    current = r.insert(0, Point(0,0));
    current = r.insert(current, Point(10,0));
    current = r.insert(current, Point(10,10));
    current = r.insert(current, Point(0,10));

    SubRegion s(r);
    CHECK(s.getFirstEdge()->begining == r.getFirstEdge()->begining);
  }
}