/**
 * This code is part of libcity library.
 *
 * @file test/testStreetGraph.h
 * @date 19.03.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @brief Unit test of Line class
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
#include "../src/geometry/line.h"
#include "../src/geometry/point.h"

SUITE(LineClass)
{
  TEST(Interface)
  {
    Line *line = new Line();

    line->setBegining(Point(0,0,0));
    line->setEnd(Point(0,0,0));
  }

  TEST(HasPoint)
  {
    Line *line = new Line(Point(0,0), Point(1,1));

    CHECK(line->hasPoint2D(Point(0,0)));
    CHECK(line->hasPoint2D(Point(1,1)));
    CHECK(line->hasPoint2D(Point(0.5,0.5)));
    CHECK(!line->hasPoint2D(Point(2,2)));

    *line = Line(Point(1,1), Point(-1,1));
    CHECK(line->hasPoint2D(Point(-0.5,1)));
  }

  TEST(Intersecting)
  {
    Line *l1 = new Line(Point(0,0), Point(1,1)),
         *l2 = new Line(Point(0,1), Point(1,0));
    Point result;

    CHECK_EQUAL(Line::INTERSECTING, l1->intersection2D(*l2, &result));
    CHECK(Point(0.5, 0.5) == result);
  }

  TEST(Intersecting2)
  {
    Line *l1 = new Line(Point(0,0), Point(1,1)),
         *l2 = new Line(Point(1,1), Point(2,2));
    Point result;

    CHECK_EQUAL(Line::INTERSECTING, l1->intersection2D(*l2, &result));
    CHECK(Point(1, 1) == result);
  }

  TEST(Intersecting3)
  {
    Line *l1 = new Line(Point(0,0), Point(1,1)),
         *l2 = new Line(Point(1,1), Point(0,5));
    Point result;

    CHECK_EQUAL(Line::INTERSECTING, l1->intersection2D(*l2, &result));
    CHECK(Point(1, 1) == result);
  }

  TEST(Nonintersecting)
  {
    Line *l1 = new Line(Point(0,0), Point(1,1)),
         *l2 = new Line(Point(2,3), Point(-3,0));
    Point result;

    CHECK_EQUAL(Line::NONINTERSECTING, l1->intersection2D(*l2, &result));
  }

  TEST(Parallel)
  {
    Line *l1 = new Line(Point(0,0), Point(1,1)),
         *l2 = new Line(Point(0,1), Point(1,2));
    Point result;

    CHECK_EQUAL(Line::NONINTERSECTING, l1->intersection2D(*l2, &result));
  }

  TEST(Coincident1)
  {
    Line *l1 = new Line(Point(0,0), Point(1,1)),
         *l2 = new Line(Point(0,0), Point(0.5,0.5));
    Point result;

    CHECK_EQUAL(Line::CONTAINING, l1->intersection2D(*l2, &result));
  }

  TEST(Coincident2)
  {
    Line *l1 = new Line(Point(0,0), Point(0.5,0.5)),
         *l2 = new Line(Point(0,0), Point(1,1));
    Point result;

    CHECK_EQUAL(Line::CONTAINED, l1->intersection2D(*l2, &result));
  }

  TEST(Coincident3)
  {
    Line *l1 = new Line(Point(0,0), Point(1,1)),
         *l2 = new Line(Point(0,0), Point(1,1));
    Point result;

    CHECK_EQUAL(Line::IDENTICAL, l1->intersection2D(*l2, &result));
  }

  TEST(Coincident4)
  {
    Line *l1 = new Line(Point(0,0), Point(1,1)),
         *l2 = new Line(Point(0.5,0.5), Point(1.5,1.5));
    Point result;

    CHECK_EQUAL(Line::OVERLAPING, l1->intersection2D(*l2, &result));
  }
}