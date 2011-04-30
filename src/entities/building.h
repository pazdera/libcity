/**
 * This code is part of libcity library.
 *
 * @file entities/building.h
 * @date 30.04.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @brief Class representing a building in the city.
 *
 */

#ifndef _BUILDING_H_
#define _BUILDING_H_

/* STL */
#include <string>

/* libcity */
#include "urbanentity.h"
#include "../lsystem/graphiclsystem.h"

class LineSegment;
class Point;
class Vector;
class Polygon;
class Zone;
class Block;
class Lot;

class Building : public UrbanEntity, public GraphicLSystem
{
  public:
    /* Available built-in types. */
    /* These must be initialized to UNIQUE values. */
    /* Initialization moved to cpp file */
    const static Type SKY_SCRAPER;

    Building();
    Building(Lot* parentAlottment);
    virtual ~Building();

    Building(Building const& source);
    Building& operator=(Building const& source);

    virtual void generate();

  protected:

  private:
    void initialize();
};

#endif
