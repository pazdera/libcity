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

class Block
{
  public:
    Block();
    Block(Polygon const& border);

    Block(Block const& source);
    Block& operator=(Block const& source);

    ~Block();

  private:
    
};


#endif
