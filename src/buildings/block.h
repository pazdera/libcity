/**
 * This code is part of libcity library.
 *
 * @file buildings/block.h
 * @date 25.04.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @brief Representation of a single block of buildings.
 *
 */

#ifndef _BLOCK_H_
#define _BLOCK_H_

#include <string>

class LineSegment;
class Point;
class Vector;
class Polygon;
class Zone;

class Block
{
  public:
    Block();
    Block(Zone* parentZone);
    Block(Zone* parentZone, Polygon const& border);

    Block(Block const& source);
    Block& operator=(Block const& source);

    ~Block();

    Polygon areaConstraints();
    void setAreaConstraints(Polygon const& area);

    void setZone(Zone* zone);
  private:
    void initialize();
    void reset();
    void freeMemory();

    Polygon* constraints;
    Zone* associatedZone;
};


#endif
