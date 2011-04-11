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
class Line;
class Path;
class StreetGraph;
class Polygon;

class RoadLSystem : public GraphicLSystem
{
  public:
    RoadLSystem();
    virtual ~RoadLSystem();

    virtual void generateRoads(int number);

    void setTarget(StreetGraph* target);

    void setAreaConstraints(Polygon *polygon);

  protected:
    virtual void interpretSymbol(char symbol);

    virtual void turnLeft();
    virtual void turnRight();

    virtual void drawLine();
    virtual bool localConstraints(Path* proposedPath);
    virtual void cancelBranch();

    virtual double getRoadSegmentLength() = 0;
    virtual double getTurnAngle() = 0;

    bool isPathInsideAreaConstraints(Path const& proposedPath);

  private:
    int generatedRoads;
    StreetGraph* targetStreetGraph;
    Polygon* areaConstraints;

    void freeAreaConstraints();
};

#endif
