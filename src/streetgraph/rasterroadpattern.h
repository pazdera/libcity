/**
 * This code is part of libcity library.
 *
 * @file streetgraph/rasterroadpattern.h
 * @date 17.03.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @brief LSystem for generating raster road patterns.
 *
 * Defines basic alphabet for road generation.
 *
 */

#ifndef _RASTERROADPATTERN_H_
#define _RASTERROADPATTERN_H_

#include "../lsystem/roadlsystem.h"

class RasterRoadPattern : public RoadLSystem
{
  public:
    RasterRoadPattern();
    virtual ~RasterRoadPattern();

  protected:
    virtual double getTurnAngle();
    virtual double getRoadSegmentLength();

  private:
    
};

#endif
