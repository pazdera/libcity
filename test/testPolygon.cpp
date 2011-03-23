/**
 * This code is part of libcity library.
 *
 * @file test/testPolygon.h
 * @date 19.03.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @brief Unit test of Polygon class
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
#include "../src/geometry/polygon.h"
#include "../src/geometry/point.h"

#include "../src/debug.h"

SUITE(PolygonClass)
{
  TEST(Interface)
  {
    Polygon *p = new Polygon();

    p->addVertex(Point(1,1));
    p->addVertex(Point(-1,1));
    p->addVertex(Point(-1,-1));
    p->addVertex(Point(1,-1));

    CHECK(p->vertex(0) == Point(1,1));
    CHECK(p->vertex(1) == Point(-1,1));
    CHECK(p->vertex(2) == Point(-1,-1));
    CHECK(p->vertex(3) == Point(1,-1));

    CHECK_EQUAL(4, p->area());
    CHECK(p->centroid() == Point(0, 0));

    CHECK(p->encloses2D(Point(0,0)));
    CHECK(p->encloses2D(Point(-1,0)));
    CHECK(p->encloses2D(Point(-0.5,0)));
    CHECK(p->encloses2D(Point(-0.5,1)));
    CHECK(p->encloses2D(Point(-0.5,0.5)));

    p->removeVertex(2);
    CHECK(p->vertex(2) == Point(1,-1));

    CHECK_EQUAL(2, p->area());

    delete p;
  }
}