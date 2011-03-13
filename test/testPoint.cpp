/**
 * This code is part of libcity library.
 *
 * @file point.class.test.h
 * @date 13.03.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @brief Unit test of Point class
 *
 * Unit tests require UnitTest++ framework! See README
 * for more informations.
 */

/* Include UnitTest++ headers.
 * Check the symlink in test/ directory */
#include <UnitTest++.h>

// Includes


// Modules
#include "../src/geometry/point.h"

SUITE(PointClass)
{
  TEST(AccessFunctions)
  {
    Point point;

    CHECK_EQUAL(point.x(), 0);
    CHECK_EQUAL(point.y(), 0);
    CHECK_EQUAL(point.z(), 0);

    point.setX(1);
    point.setY(2);
    point.setZ(3);
    CHECK_EQUAL(point.x(), 1);
    CHECK_EQUAL(point.y(), 2);
    CHECK_EQUAL(point.z(), 3);

    point = Point(-1, -7);
    CHECK_EQUAL(point.x(), -1);
    CHECK_EQUAL(point.y(), -7);
    CHECK_EQUAL(point.z(), 0);

    point = Point(5, 6.3, 8.2);
    CHECK_EQUAL(point.x(), 5);
    CHECK_EQUAL(point.y(), 6.3);
    CHECK_EQUAL(point.z(), 8.2);

    point.set(1, 2, 3);
    CHECK_EQUAL(point.x(), 1);
    CHECK_EQUAL(point.y(), 2);
    CHECK_EQUAL(point.z(), 3);
  }

  TEST(Operators)
  {
    Point p1, p2;
    CHECK(p1 == p2);

    p1.set(1.3, 2.2 ,3.1);
    p2.set(1.3, 2.2 ,3.1);
    CHECK(p1 == p2);
  }
}