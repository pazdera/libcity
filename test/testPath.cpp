/**
 * This code is part of libcity library.
 *
 * @file test/testPath.cpp
 * @date 15.04.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @brief Unit test of Path class
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
#include "../src/streetgraph/path.h"
#include "../src/geometry/vector.h"
#include "../src/geometry/point.h"
#include "../src/geometry/linesegment.h"
#include "../src/debug.h"

SUITE(PathClass)
{
  TEST(DirectionVectors)
  {
    Path path(LineSegment(Point(0,0), Point(10,10)));
    Vector correct;

    correct = Vector(-1,-1);
    correct.normalize();
    CHECK(correct == path.beginingDirectionVector());

    correct = Vector(1,1);
    correct.normalize();
    CHECK(correct == path.endDirectionVector());

    path.setBegining(Point(10,10));
    path.setEnd(Point(-10,-10));

    correct = Vector(1,1);
    correct.normalize();
    CHECK(correct == path.beginingDirectionVector());

    correct = Vector(-1,-1);
    correct.normalize();
    CHECK(correct == path.endDirectionVector());
  }
}