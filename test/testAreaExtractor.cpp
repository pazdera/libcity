/**
 * This code is part of libcity library.
 *
 * @file test/testAreaExtractor.cpp
 * @date 31.03.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @brief Unit test of AreaExtractor class
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
#include "../src/streetgraph/streetgraph.h"
#include "../src/streetgraph/areaextractor.h"
#include "../src/streetgraph/rasterroadpattern.h"
#include "../src/geometry/polygon.h"
#include "../src/area/block.h"
#include "../src/area/zone.h"
#include "../src/streetgraph/path.h"
#include "../src/geometry/point.h"
#include "../src/geometry/line.h"
#include "../src/geometry/linesegment.h"
#include "../src/debug.h"

SUITE(MCBClass)
{
  TEST(OneCycle)
  {
    AreaExtractor* mcb = 0;
    StreetGraph *sg = new StreetGraph();

    sg->addRoad(Path(LineSegment(Point(-100,100), Point(100,100))));
    sg->addRoad(Path(LineSegment(Point(100,100), Point(100,-100))));
    sg->addRoad(Path(LineSegment(Point(100,-100), Point(-100,-100))));
    sg->addRoad(Path(LineSegment(Point(-100,-100), Point(-100,100))));

    mcb = new AreaExtractor();

    std::list<Zone*> cycles = mcb->extractZones(sg);
    CHECK(1 == cycles.size());
  }

  TEST(Filament)
  {
    AreaExtractor* mcb = 0;
    StreetGraph *sg = new StreetGraph();

    sg->addRoad(Path(LineSegment(Point(-100,100), Point(100,100))));

    mcb = new AreaExtractor();

    std::list<Zone*> cycles = mcb->extractZones(sg);
    CHECK(0 == cycles.size());
  }

  TEST(CycleOutOfZone)
  {
    AreaExtractor* mcb = 0;
    StreetGraph *sg = new StreetGraph();

    sg->addRoad(Path(LineSegment(Point(-100,100), Point(100,100))));
    sg->addRoad(Path(LineSegment(Point(100,100), Point(100,-100))));
    sg->addRoad(Path(LineSegment(Point(100,-100), Point(-100,-100))));
    sg->addRoad(Path(LineSegment(Point(-100,-100), Point(-100,100))));

    Polygon *constraints = new Polygon;
    constraints->addVertex(Point(-1000,-900));
    constraints->addVertex(Point(-1000,-800));
    constraints->addVertex(Point(-500,-800));

    Zone* zone = new Zone(sg);
    zone->setAreaConstraints(*constraints);
    mcb = new AreaExtractor();

    std::list<Zone*> cycles = mcb->extractZones(sg, zone);
    CHECK(0 == cycles.size());
  }

  TEST(ExtractZones)
  {
    AreaExtractor* mcb = 0;
    StreetGraph *sg = new StreetGraph();

    /* First 2 cycles */
    sg->addRoad(Path(LineSegment(Point(-100,100), Point(100,100))));
    sg->addRoad(Path(LineSegment(Point(100,100), Point(100,-100))));
    sg->addRoad(Path(LineSegment(Point(100,-100), Point(-100,-100))));
    sg->addRoad(Path(LineSegment(Point(-100,-100), Point(-100,100))));
    sg->addRoad(Path(LineSegment(Point(-100,-100), Point(100,100))));

    /* Second cycle */
    sg->addRoad(Path(LineSegment(Point(-100,100), Point(0,200))));
    sg->addRoad(Path(LineSegment(Point(0,200), Point(100,100))));

    /* Filament */
    sg->addRoad(Path(LineSegment(Point(100,-100), Point(100,-200))));

    Polygon *constraints = new Polygon;
    constraints->addVertex(Point(-100,100));
    constraints->addVertex(Point(100,100));
    constraints->addVertex(Point(100,-100));
    constraints->addVertex(Point(-100,-100));

    Zone* zone = new Zone(sg);
    zone->setAreaConstraints(*constraints);
    mcb = new AreaExtractor();

    std::list<Zone*> cycles = mcb->extractZones(sg, zone);
    CHECK(2 == cycles.size());
  }

  TEST(ExtractBlocks)
  {
    AreaExtractor* mcb = 0;
    StreetGraph *sg = new StreetGraph();

    /* First 2 cycles */
    sg->addRoad(Path(LineSegment(Point(-100,100), Point(100,100))));
    sg->addRoad(Path(LineSegment(Point(100,100), Point(100,-100))));
    sg->addRoad(Path(LineSegment(Point(100,-100), Point(-100,-100))));
    sg->addRoad(Path(LineSegment(Point(-100,-100), Point(-100,100))));

    sg->addRoad(Path(LineSegment(Point(-100,-100), Point(100,100))));

    /* Second cycle */
    sg->addRoad(Path(LineSegment(Point(-100,100), Point(0,200))));
    sg->addRoad(Path(LineSegment(Point(0,200), Point(100,100))));

    /* Filament */
    sg->addRoad(Path(LineSegment(Point(100,-100), Point(100,-200))));

    Polygon *constraints = new Polygon;
    constraints->addVertex(Point(-100,100));
    constraints->addVertex(Point(100,100));
    constraints->addVertex(Point(100,-100));
    constraints->addVertex(Point(-100,-100));

    Zone* zone = new Zone(sg);
    zone->setAreaConstraints(*constraints);
    mcb = new AreaExtractor();
    mcb->setRoadWidth(Road::PRIMARY_ROAD, 10);

    std::list<Block*> cycles = mcb->extractBlocks(sg, zone);
    CHECK(2 == cycles.size());
  }
}