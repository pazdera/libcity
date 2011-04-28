/**
 * This code is part of libcity library.
 *
 * @file area/area.h
 * @date 26.04.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @brief Base class for city areas (zones, districts, blocks, alottments).
 *
 */

#ifndef _AREA_H_
#define _AREA_H_

/* STL */
#include <vector>
#include <list>
#include <map>

class Polygon;
class StreetGraph;
class RoadLSystem;
class Intersection;
class Block;

class Area;
class Area
{
  public:
    Area();
    virtual ~Area();

    Area(Area const& source);
    Area& operator=(Area const& source);

    virtual void setAreaConstraints(Polygon const& area);
    virtual Polygon areaConstraints();

    virtual void setParent(Area* area);
    virtual Area* parent();

  protected:
    Polygon* constraints;
    Area* parentArea;

  private:
    void initialize();
    void freeMemory();
};

#endif