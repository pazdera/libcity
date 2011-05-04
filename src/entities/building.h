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
#include <list>

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
class Shape;

class Building : public UrbanEntity, public GraphicLSystem
{
  private:
    Building();

  public:
    Building(Lot* parentAlottment);
    virtual ~Building();

    Building(Building const& source);
    Building& operator=(Building const& source);

    double maxHeight();
    void setMaxHeight(double maxHeight);

    void pushBoundingBox();
    void popBoundingBox();

    virtual void interpretSymbol(char symbol);

    //virtual void draw() = 0;

  protected:
    /**
      Maximum height together with the lot in which this
      building resides defines bounding box. */
    Shape* boundingBox;

    std::list<Shape*> boundingBoxStack;

  private:
    void initialize();
    void freeMemory();
};

#endif
