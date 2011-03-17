/**
 * This code is part of libcity library.
 *
 * @file lsystem/roadlsystem.h
 * @date 12.03.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @brief Base class for Road generators
 *
 * @see LSystem
 * @see GraphicsLSystem
 *
 */

#ifndef _ROADLSYSTEM_H_
#define _ROADLSYSTEM_H_

#include "graphiclsystem.h"

class Point;
class Vector;
class Road;

class RoadLSystem : public GraphicLSystem
{
  public:
    RoadLSystem();
    virtual ~RoadLSystem();

    Road* getNextIdealRoadSegment();

  protected:
    virtual void interpretSymbol(char symbol);

    virtual void turnLeft()  = 0;
    virtual void turnRight() = 0;

    virtual void drawLine();

    virtual double getRoadSegmentLength() = 0;
    virtual double getTurningAngle() = 0;
  private:
    
};

#endif
