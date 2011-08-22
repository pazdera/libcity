/**
 * This code is part of libcity library.
 *
 * @file test/testShape.cpp
 * @date 01.05.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @brief Unit test of Shape class
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
#include "../src/geometry/point.h"
#include "../src/geometry/polygon.h"
#include "../src/geometry/shape.h"
#include "../src/debug.h"

SUITE(ShapeClass)
{
  TEST(Interface)
  {
    Polygon p;
    p.addVertex(Point(0,0));
    p.addVertex(Point(10,0));
    p.addVertex(Point(10,10));
    p.addVertex(Point(0,10));

    Shape s;
    s.setBase(p);
    s.setHeight(10);

    CHECK(s.base().vertex(0) == p.vertex(0));
    CHECK(s.base().vertex(3) == p.vertex(3));
    CHECK(s.height() == 10);
  }

  TEST(EnclosesPoint)
  {
    Polygon p;
    p.addVertex(Point(0,0));
    p.addVertex(Point(10,0));
    p.addVertex(Point(10,10));
    p.addVertex(Point(0,10));

    Shape s;
    s.setBase(p);
    s.setHeight(10);

    CHECK(s.encloses(Point(0,0,0)));
    CHECK(s.encloses(Point(5,5,5)));
    CHECK(!s.encloses(Point(15,15,15)));
  }

  TEST(EnclosesShape)
  {
    Polygon p;
    p.addVertex(Point(0,0));
    p.addVertex(Point(10,0));
    p.addVertex(Point(10,10));
    p.addVertex(Point(0,10));

    Polygon p2(p);
    p2.substract(1);
    Shape insider;
    insider.setBase(p2);
    insider.setHeight(10);

    Shape s;
    s.setBase(p);
    s.setHeight(10);

    CHECK(s.encloses(insider));
    CHECK(s.encloses(s));

    p2.substract(-5);
    insider.setBase(p2);
    CHECK(!s.encloses(insider));
  }
}