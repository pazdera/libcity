/**
 * This code is part of libcity library.
 *
 * @file test/testLineSegment.cpp
 * @date 19.03.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @brief Unit test of LineSegment class
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
#include "../src/geometry/linesegment.h"
#include "../src/geometry/units.h"
#include "../src/geometry/point.h"
#include "../src/geometry/polygon.h"

#include "../src/debug.h"

SUITE(LineSegmentClass)
{
  TEST(Interface)
  {
    LineSegment *line = new LineSegment();

    line->setBegining(Point(0,0,0));
    line->setEnd(Point(0,0,0));

    delete line;
  }

  TEST(HasPoint)
  {
    LineSegment *line = new LineSegment(Point(0,0), Point(1,1));

    CHECK(line->hasPoint2D(Point(0,0)));
    CHECK(line->hasPoint2D(Point(1,1)));
    CHECK(line->hasPoint2D(Point(0.5,0.5)));
    CHECK(!line->hasPoint2D(Point(2,2)));

    *line = LineSegment(Point(1,1), Point(-1,1));
    CHECK(line->hasPoint2D(Point(-0.5,1)));

    delete line;
  }

  TEST(HasPoint2)
  {
    LineSegment *line = new LineSegment(Point(1,1), Point(0,0));

    CHECK(line->hasPoint2D(Point(0,0)));
    CHECK(line->hasPoint2D(Point(1,1)));
    CHECK(line->hasPoint2D(Point(0.5,0.5)));
    CHECK(!line->hasPoint2D(Point(2,2)));

    *line = LineSegment(Point(1,1), Point(-1,1));
    CHECK(line->hasPoint2D(Point(-0.5,1)));

    delete line;
  }

  TEST(Intersecting)
  {
    LineSegment *l1 = new LineSegment(Point(0,0), Point(1,1)),
                *l2 = new LineSegment(Point(0,1), Point(1,0));
    Point result;

    CHECK_EQUAL(LineSegment::INTERSECTING, l1->intersection2D(*l2, &result));
    CHECK(Point(0.5, 0.5) == result);

    delete l1;
    delete l2;
  }

  TEST(Intersecting2)
  {
    LineSegment *l1 = new LineSegment(Point(0,0), Point(1,1)),
                *l2 = new LineSegment(Point(1,1), Point(2,2));
    Point result;

    CHECK_EQUAL(LineSegment::INTERSECTING, l1->intersection2D(*l2, &result));
    CHECK(Point(1, 1) == result);

    delete l1;
    delete l2;
  }

  TEST(Intersecting3)
  {
    LineSegment *l1 = new LineSegment(Point(0,0), Point(1,1)),
         *l2 = new LineSegment(Point(1,1), Point(0,5));
    Point result;

    CHECK_EQUAL(LineSegment::INTERSECTING, l1->intersection2D(*l2, &result));
    CHECK(Point(1, 1) == result);

    delete l1;
    delete l2;
  }

  TEST(Nonintersecting)
  {
    LineSegment *l1 = new LineSegment(Point(0,0), Point(1,1)),
         *l2 = new LineSegment(Point(2,3), Point(-3,0));
    Point result;

    CHECK_EQUAL(LineSegment::NONINTERSECTING, l1->intersection2D(*l2, &result));

    delete l1;
    delete l2;
  }

  TEST(Parallel)
  {
    LineSegment *l1 = new LineSegment(Point(0,0), Point(1,1)),
         *l2 = new LineSegment(Point(0,1), Point(1,2));
    Point result;

    CHECK_EQUAL(LineSegment::NONINTERSECTING, l1->intersection2D(*l2, &result));

    delete l1;
    delete l2;
  }

  TEST(Coincident1)
  {
    LineSegment *l1 = new LineSegment(Point(0,0), Point(1,1)),
         *l2 = new LineSegment(Point(0,0), Point(0.5,0.5));
    Point result;

    CHECK_EQUAL(LineSegment::CONTAINING, l1->intersection2D(*l2, &result));

    delete l1;
    delete l2;
  }

  TEST(Coincident2)
  {
    LineSegment *l1 = new LineSegment(Point(0,0), Point(0.5,0.5)),
         *l2 = new LineSegment(Point(0,0), Point(1,1));
    Point result;

    CHECK_EQUAL(LineSegment::CONTAINED, l1->intersection2D(*l2, &result));

    delete l1;
    delete l2;
  }

  TEST(Coincident3)
  {
    LineSegment *l1 = new LineSegment(Point(0,0), Point(1,1)),
         *l2 = new LineSegment(Point(0,0), Point(1,1));
    Point result;

    CHECK_EQUAL(LineSegment::IDENTICAL, l1->intersection2D(*l2, &result));

    delete l1;
    delete l2;
  }

  TEST(Coincident4)
  {
    LineSegment *l1 = new LineSegment(Point(0,0), Point(1,1)),
         *l2 = new LineSegment(Point(0.5,0.5), Point(1.5,1.5));
    Point result;

    CHECK_EQUAL(LineSegment::OVERLAPING, l1->intersection2D(*l2, &result));

    delete l1;
    delete l2;
  }

//   TEST(TrimByPolygon)
//   {
//     LineSegment *line = new Line;
//     Polygon *polygon = new Polygon();
// 
//     polygon->addVertex(Point(1,1));
//     polygon->addVertex(Point(-1,1));
//     polygon->addVertex(Point(-1,-1));
//     polygon->addVertex(Point(1,-1));
// 
//     *line = Line(Point(0,0), Point(10,10));
//     line->trimOverlapingPart(*polygon);
//     CHECK(*line == LineSegment(Point(0,0), Point(1,1)));
// 
//     *line = LineSegment(Point(0,0), Point(0,10));
//     line->trimOverlapingPart(*polygon);
//     CHECK(*line == LineSegment(Point(0,0), Point(0,1)));
// 
//     *line = LineSegment(Point(0,1), Point(10,1));
//     line->trimOverlapingPart(*polygon);
//     CHECK(*line == LineSegment(Point(0,1), Point(1,1)));
// 
//     delete line;
//     delete polygon;
//   }

  TEST(WeirdCase)
  {
    LineSegment *l1 = new LineSegment(Point(57.8629, 218.793, 0), Point(77.2648, 197.245, 0)),
         *l2 = new LineSegment(Point(57.8629, 218.793, 0), Point(77.2648, 197.245, 0));

    Point intersection;

    CHECK_EQUAL(LineSegment::IDENTICAL, l1->intersection2D(*l2, &intersection));

    delete l1;
    delete l2;
  }

  TEST(PointDistance)
  {
    LineSegment l(Point(0,0), Point(10,10));

    CHECK_CLOSE(sqrt(2), l.distance(Point(-1,-1)), libcity::EPSILON);
    CHECK_CLOSE(sqrt(2), l.distance(Point(11,11)), libcity::EPSILON);
    CHECK_CLOSE(sqrt(2)/2, l.distance(Point(3,4)), libcity::EPSILON);
    CHECK_CLOSE(sqrt(2)/2, l.distance(Point(4,3)), libcity::EPSILON);
  }

  TEST(Contained)
  {
    LineSegment a = LineSegment(Point(-3000, -2509.3, 0), Point(-3000, -2244.59, 0));
    LineSegment b = LineSegment(Point(-3000, 837.305, 0), Point(-3000, -2509.3, 0));

    LineSegment::Intersection result;
    Point point;
    result = a.intersection2D(b, &point);

    CHECK(LineSegment::CONTAINED == result);

    result = b.intersection2D(a, &point);
    CHECK(LineSegment::CONTAINING == result);
  }

}