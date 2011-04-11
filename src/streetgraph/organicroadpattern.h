/**
 * This code is part of libcity library.
 *
 * @file streetgraph/organicroadpattern.h
 * @date 11.04.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @brief LSystem for generating organic road patterns.
 *
 *
 */

#ifndef _ORGANICROADPATTERN_H_
#define _ORGANICROADPATTERN_H_

#include "../lsystem/roadlsystem.h"

class OrganicRoadPattern : public RoadLSystem
{
  public:
    OrganicRoadPattern();
    virtual ~OrganicRoadPattern();

  protected:
    virtual double getTurnAngle();
    virtual double getRoadSegmentLength();

  private:

};

#endif
