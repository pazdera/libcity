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
#include "../streetgraph/road.h"

class Point;
class Vector;
class LineSegment;
class Path;
class StreetGraph;
class Polygon;

class RoadLSystem : public GraphicLSystem
{
  public:
    RoadLSystem();
    virtual ~RoadLSystem();

    virtual bool generateRoads(int number);
    virtual void generate();

    void setTarget(StreetGraph* target);

    void setAreaConstraints(Polygon *polygon);

    void setRoadType(Road::Type type);
    void setRoadLength(double min, double max);
    void setTurnAngle(double min, double max);
    void setSnapDistance(double distance);

  protected:
    virtual void interpretSymbol(char symbol);

    virtual void turnLeft();
    virtual void turnRight();

    virtual void drawRoad();
    virtual bool localConstraints(Path* proposedPath);
    virtual void cancelBranch();

    virtual double getRoadSegmentLength();
    virtual double getTurnAngle();

    bool isPathInsideAreaConstraints(Path* proposedPath);

     bool checkSnapPossibility(Path* proposedPath, Intersection* intersection);
     bool checkSnapPossibility(Path* proposedPath, Road* road);

  private:
    const static double MINIMAL_ROAD_LENGTH;

    int generatedRoads;
    StreetGraph* targetStreetGraph;
    Polygon* areaConstraints;

    double snapDistance;

    Road::Type generatedType;
    double minRoadLength;
    double maxRoadLength;
    double minTurnAngle;
    double maxTurnAngle;

    void freeAreaConstraints();
};

#endif
