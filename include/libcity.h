/**
 * This code is part of libcity library.
 *
 * @file libcity.h
 * @date 13.03.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @brief Lib header
 *
 */

#ifndef __LIBCITY_H_
#define __LIBCITY_H_

namespace libcity
{
  #include "geometry/point.h"
  #include "geometry/line.h"
  #include "geometry/vector.h"
  #include "geometry/polygon.h"

  #include "streetgraph/road.h"
  #include "streetgraph/intersection.h"
  #include "streetgraph/streetgraph.h"
  #include "streetgraph/rasterroadpattern.h"
  #include "streetgraph/organicroadpattern.h"
  #include "streetgraph/minimalcyclebasis.h"

  #include "lsystem/lsystem.h"
  #include "lsystem/graphiclsystem.h"
  #include "lsystem/roadlsystem.h"

  #include "random.h"
  #include "city.h"
  #include "debug.h"
}

#endif