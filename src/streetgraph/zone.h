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

class Polygon;
class StreetGraph;
class RoadLSystem;

class Zone
{
  public:
    Zone(StreetGraph* streets);
    ~Zone();

    Zone(Zone const& source);
    Zone& operator=(Zone const& source);

    void setRoadGenerator(RoadLSystem* generator);
    void setAreaConstraints(Polygon const& area);

    Polygon areaConstraints();

  private:
    Polygon* constraints;
    RoadLSystem* roadGenerator;
    StreetGraph* associatedStreetGraph;

    void initialize();
    void freeMemory();
    void freeRoadGenerator();

    void setStreetGraph(StreetGraph* streets);
};

#endif