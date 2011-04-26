/**
 * This code is part of libcity library.
 *
 * @file area/zone.h
 * @date 02.03.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @brief Representation of a city district or zone.
 *
 */

#ifndef _ZONE_H_
#define _ZONE_H_

/* STL */
#include <vector>
#include <list>
#include <map>

/* libcity */
#include "../streetgraph/road.h"
#include "area.h"

class Polygon;
class StreetGraph;
class RoadLSystem;
class Intersection;
class Block;

class Zone : public Area
{
  public:
    Zone(StreetGraph* streets);
    ~Zone();

    Zone(Zone const& source);
    Zone& operator=(Zone const& source);

    void setRoadGenerator(RoadLSystem* generator);

    StreetGraph* streetGraph();
    void setStreetGraph(StreetGraph* streets);

    bool isIntersectionInside(Intersection* intersection);
    bool roadIsInside(Road* road);

    void createBlocks(std::map<Road::Types, double> roadWidths);
    std::list<Block*> getBlocks();

  private:
    RoadLSystem* roadGenerator;
    StreetGraph* associatedStreetGraph;

    std::list<Block*>* blocks;

    void initialize();
    void freeMemory();
    void freeRoadGenerator();
};

#endif