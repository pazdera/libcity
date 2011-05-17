/**
 * This code is part of libcity library.
 *
 * @file libcity.h
 * @date 13.03.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @brief Lib header
 *
 * @mainpage libcity documentation
 *   Welcome to libcity documentation. Hopefully you'll find here
 *   exactly what you need!
 *
 * @section license License
@verbatim
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
@endverbatim
 *
 */


#ifndef __LIBCITY_H_
#define __LIBCITY_H_

#include "geometry/point.h"
#include "geometry/line.h"
#include "geometry/linesegment.h"
#include "geometry/vector.h"
#include "geometry/polygon.h"
#include "geometry/ray.h"
#include "geometry/shape.h"

#include "streetgraph/road.h"
#include "streetgraph/path.h"
#include "streetgraph/intersection.h"
#include "streetgraph/streetgraph.h"
#include "streetgraph/rasterroadpattern.h"
#include "streetgraph/organicroadpattern.h"
#include "streetgraph/areaextractor.h"

#include "area/area.h"
#include "area/zone.h"
#include "area/block.h"
#include "area/lot.h"
#include "area/subregion.h"

#include "lsystem/lsystem.h"
#include "lsystem/graphiclsystem.h"
#include "lsystem/roadlsystem.h"

#include "entities/urbanentity.h"
#include "entities/building.h"

#include "random.h"
#include "city.h"
#include "debug.h"

#endif
