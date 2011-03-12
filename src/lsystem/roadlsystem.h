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

class RoadLSystem : public GraphicLSystem
{
  public:
    RoadLSystem();
    virtual ~RoadLSystem();

    void setPosition(Point position);
    void setDirection(Vector direction);

  protected:

};

#endif
