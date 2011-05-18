/**
 * This code is part of libcity library.
 *
 * @file city.h
 * @date 06.03.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @brief Library interface for the city creation process.
 *
 */

#ifndef _CITY_H_
#define _CITY_H_

#include <list>

class StreetGraph;
class Zone;
class Polygon;

class City
{
  public:
    City();
    virtual ~City();

    virtual void generate();

  private: /* Copying not allowed */
    City(City const& source);
    City& operator=(City const& source);

  protected:
    virtual void createPrimaryRoadNetwork() = 0;
    virtual void createZones() = 0;
    virtual void createSecondaryRoadNetwork() = 0;
    virtual void createBlocks() = 0;
    virtual void createBuildings() = 0;

    StreetGraph* map;
    std::list<Zone*> *zones;

    Polygon* area;

  private:
    void initialize();
    void freeMemory();
};

#endif