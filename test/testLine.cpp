/**
 * This code is part of libcity library.
 *
 * @file test/testLine.cpp
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
#include <cmath>

// Tested modules
#include "../src/geometry/line.h"
#include "../src/geometry/units.h"
#include "../src/geometry/point.h"
#include "../src/geometry/polygon.h"

#include "../src/debug.h"

SUITE(LineClass)
{
  TEST(Interface)
  {
    Line *line = new Line();

    line->setBegining(Point(0,0,0));
    line->setEnd(Point(0,0,0));

    CHECK(Point(0,0,0) == line->begining());
    CHECK(Point(0,0,0) == line->end());

    delete line;
  }

  TEST(HasPoint)
  {
    Line *line = new Line(Point(0,0), Point(1,1));

    CHECK(line->hasPoint2D(Point(0,0)));
    CHECK(line->hasPoint2D(Point(1,1)));
    CHECK(line->hasPoint2D(Point(0.5,0.5)));
    CHECK(line->hasPoint2D(Point(2,2)));
    CHECK(!line->hasPoint2D(Point(3,4)));

    *line = Line(Point(1,1), Point(-1,1));
    CHECK(line->hasPoint2D(Point(-0.5,1)));

    delete line;
  }

  TEST(Intersecting)
  {
    Line *l1 = new Line(Point(0,0), Point(1,1)),
         *l2 = new Line(Point(0,1), Point(1,0));
    Point result;

    CHECK_EQUAL(Line::INTERSECTING, l1->intersection2D(*l2, &result));
    CHECK(Point(0.5, 0.5) == result);

    delete l1;
    delete l2;
  }

  TEST(Parallel)
  {
    Line *l1 = new Line(Point(0,0), Point(1,1)),
         *l2 = new Line(Point(1,1), Point(2,2));
    Point result;

    CHECK_EQUAL(Line::PARALLEL, l1->intersection2D(*l2, &result));

    delete l1;
    delete l2;
  }

  TEST(Identical)
  {
    Line *l1 = new Line(Point(0,0), Point(1,1)),
         *l2 = new Line(Point(0,0), Point(1,1));
    Point result;

    CHECK_EQUAL(Line::PARALLEL, l1->intersection2D(*l2, &result));

    delete l1;
    delete l2;
  }

  TEST(PointDistance)
  {
    Line l(Point(0,0), Point(10,10));

    CHECK_CLOSE(0, l.distance(Point(-1,-1)), libcity::EPSILON);
    CHECK_CLOSE(0, l.distance(Point(11,11)), libcity::EPSILON);
    CHECK_CLOSE(sqrt(2)/2, l.distance(Point(3,4)), libcity::EPSILON);
    CHECK_CLOSE(sqrt(2)/2, l.distance(Point(4,3)), libcity::EPSILON);
  }
}