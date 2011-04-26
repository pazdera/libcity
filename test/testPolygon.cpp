/**
 * This code is part of libcity library.
 *
 * @file test/testPolygon.cpp
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
#include "../src/geometry/linesegment.h"
#include "../src/geometry/vector.h"

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

  TEST(centroid)
  {
    Polygon *p = new Polygon();

    p->addVertex(Point(0,0));
    p->addVertex(Point(0,10));
    p->addVertex(Point(10,10));
    p->addVertex(Point(10,0));


    CHECK(p->centroid() == Point(5, 5));
    
    delete p;

    p = new Polygon();

    p->addVertex(Point(-10,-10));
    p->addVertex(Point(-10,10));
    p->addVertex(Point(10,10));
    p->addVertex(Point(10,-10));


    CHECK(p->centroid() == Point(0, 0));

    delete p;
  }

  TEST(EdgeAccess)
  {
    Polygon p;

    p.addVertex(Point(0,0));
    p.addVertex(Point(1,1));
    CHECK(LineSegment(Point(0,0), Point(1,1)) == p.edge(0));

    p.addVertex(Point(1,0));
    CHECK(LineSegment(Point(0,0), Point(1,1)) == p.edge(0));
  }

  TEST(Normal)
  {
    Polygon p;

    p.addVertex(Point(0,0));
    p.addVertex(Point(1,1));
    p.addVertex(Point(1,0));
    p.addVertex(Point(10,10));
    p.addVertex(Point(10,20));
    CHECK(Vector(0,0,1) == p.normal());
  }

  TEST(EdgeNormal)
  {
    Polygon p;
    p.addVertex(Point(0,0));
    p.addVertex(Point(10,10));
    p.addVertex(Point(10,0));
    CHECK(Vector(-1,0) == p.edgeNormal(1));
  }

  TEST(EdgeNormal2)
  {
    Polygon p;
    p.addVertex(Point(0,0));
    p.addVertex(Point(0,10));
    p.addVertex(Point(10,10));

    CHECK(Vector(0,-1) == p.edgeNormal(1));
  }

  TEST(EdgeNormal3)
  {
    Polygon p;
    p.addVertex(Point(-10,-10));
    p.addVertex(Point(-10,10));
    p.addVertex(Point(10,10));
    p.addVertex(Point(10,-10));

    CHECK(Vector(1,0) == p.edgeNormal(0));
    CHECK(Vector(0,-1) == p.edgeNormal(1));
  }

  TEST(EdgeNormal4)
  {
    Polygon p(Point(-100, -100, 0), Point(100, -100, 0), Point(100, 100, 0));

    CHECK(Vector(0,1,0) == p.edgeNormal(0));
  }
}