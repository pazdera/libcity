/**
 * This code is part of libcity library.
 *
 * @file streetgraph/zone.h
 * @date 02.03.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @brief !!! NOT SURE YET
 *
 */

#ifndef _ZONE_H_
#define _ZONE_H_

#include <vector>
#include <list>
#include <map>

#include "road.h"

class Polygon;
class StreetGraph;
class RoadLSystem;
class Intersection;
class Block;

class Zone
{
  public:
    Zone(StreetGraph* streets);
    ~Zone();

    Zone(Zone const& source);
    Zone& operator=(Zone const& source);

    void setRoadGenerator(RoadLSystem* generator);
    void setAreaConstraints(Polygon const& area);

    StreetGraph* streetGraph();
    Polygon areaConstraints();

    bool isIntersectionInside(Intersection* intersection);
    bool roadIsInside(Road* road);

    void createBlocks(std::map<Road::Types, double> roadWidths);
    std::list<Block*> getBlocks();

  private:
    Polygon* constraints;
    RoadLSystem* roadGenerator;
    StreetGraph* associatedStreetGraph;

    std::list<Block*>* blocks;

    void initialize();
    void freeMemory();
    void freeRoadGenerator();

    void setStreetGraph(StreetGraph* streets);
};

#endif