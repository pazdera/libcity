/**
 * This code is part of libcity library.
 *
 * @file area/block.h
 * @date 25.04.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @brief Representation of a single block of buildings.
 *
 */

#ifndef _BLOCK_H_
#define _BLOCK_H_

/* STL */
#include <string>

/* libcity */
#include "area.h"

class LineSegment;
class Point;
class Vector;
class Polygon;
class Zone;
class Lot;
class SubRegion;

/**
  Area that represents a building block.
  That is an area enclosed by a loop in a street graph.
  Blocks are grouped to zones. Each block can be subdivided
  into allotments */
class Block : public Area
{
  public:
    Block();
    Block(Zone* parentZone);
    Block(Zone* parentZone, Polygon const& border);

    Block(Block const& source);
    Block& operator=(Block const& source);

    ~Block();

    /**
     Subdivision algorithm that subdivides a signle block
     into a list of smaller areas - allotments.
      @param[in] lotWidth Desired width of lots.
      @param[in] lotHeight Desired height of lots.
      @param[in] deviance Deviance factor in lot creation.

      @return Lost of lots.
     */
    void createLots(double lotWidth, double lotHeight, double deviance);
    std::list<Lot*> getLots();

  private:

    Point calcSplitPoint(LineSegment const& longestEdge, double splitSize, double lotDeviance);
    std::list<SubRegion*> splitRegion(SubRegion* area, Point a, Point b);

    std::list<Lot*> lots;

    void initialize();
    void freeMemory();
};


#endif
