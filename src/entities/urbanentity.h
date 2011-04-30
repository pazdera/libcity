/**
 * This code is part of libcity library.
 *
 * @file entities/urbanentity.h
 * @date 30.04.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @brief Abstract class representing an object or entity in the city.
 * This covers objects like buildings, woods, squares ...
 *
 */

#ifndef _URBAN_ENTITY_H_
#define _URBAN_ENTITY_H_

/* STL */
#include <string>

/* libcity */
#include "urbanentity.h"

class LineSegment;
class Point;
class Vector;
class Polygon;
class Zone;
class Block;
class Lot;

class UrbanEntity
{
  public:
    typedef short int Type;
    static Type defineNewEntityType();

    /* Available built-in types. */
    /* These must be initialized to UNIQUE values. */
    static const Type BUILDING = 0;

    virtual Type type();
    virtual void setType(Type const& typeId);

    Lot* lot();
    void setLot(Lot* parentAlottment);

    UrbanEntity();
    UrbanEntity(Lot* parentAlottment);
    virtual ~UrbanEntity();

    virtual void generate() = 0;

  protected:
    Lot* parentLot;

  private:
    /** Must be initialized to a proper value.
    There is ONE predefined entity. So in this case
    it ought be set to a number above 1. */
    static unsigned int numberOfDefinedEntityTypes;
    Type entityType;
};

#endif
