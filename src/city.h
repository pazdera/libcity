/**
 * This code is part of libcity library.
 *
 * @file city.h
 * @date 06.03.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @brief !!! NOT SURE YET
 *
 */

#ifndef _CITY_H_
#define _CITY_H_

#include <list>

class StreetGraph;
class Zone;

class City
{
  public:
    City();
    virtual ~City();

  private: /* Copying not allowed */
    City(City const& source);
    City& operator=(City const& source);

  protected:
    virtual void createPrimaryRoadNetwork() = 0;
    virtual void createZones() = 0;
    virtual void createSecondaryRoadNetwork() = 0;
    virtual void createBlocks() = 0;
    virtual void createBuildings() = 0;
  public:
    virtual void generate();

  protected:
    virtual void drawRoadNetwork() = 0;
    virtual void drawBuildings() = 0;
  public:
    virtual void draw();

  private:
    StreetGraph* map;
    std::list<Zone*> *zones;

    void initialize();
    void freeMemory();
};

#endif