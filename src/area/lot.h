/**
 * This code is part of libcity library.
 *
 * @file area/lot.h
 * @date 26.04.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @brief Representation of a building lot.
 * A parcel that will later be used as a place for a building construction.
 *
 */

#ifndef _LOT_H_
#define _LOT_H_

/* STL */
#include <string>

/* libcity */
#include "area.h"

class LineSegment;
class Point;
class Vector;
class Polygon;
class Zone;
class Block;

class Lot : public Area
{
  public:
    Lot();
    Lot(Block* parentBlock);

    Lot(Lot const& source);
    Lot& operator=(Lot const& source);

    ~Lot();

  private:
    void initialize();
    void freeMemory();

    /* Building */
};


#endif
