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

#include "../src/geometry/point.h"
#include "../src/geometry/line.h"
#include "../src/geometry/linesegment.h"
#include "../src/geometry/vector.h"
#include "../src/geometry/polygon.h"
#include "../src/geometry/ray.h"

#include "../src/streetgraph/road.h"
#include "../src/streetgraph/path.h"
#include "../src/streetgraph/intersection.h"
#include "../src/streetgraph/streetgraph.h"
#include "../src/streetgraph/rasterroadpattern.h"
#include "../src/streetgraph/organicroadpattern.h"
#include "../src/streetgraph/areaextractor.h"

#include "../src/area/area.h"
#include "../src/area/zone.h"
#include "../src/area/block.h"
#include "../src/area/lot.h"
#include "../src/area/subregion.h"


#include "../src/lsystem/lsystem.h"
#include "../src/lsystem/graphiclsystem.h"
#include "../src/lsystem/roadlsystem.h"

#include "../src/random.h"
#include "../src/city.h"
#include "../src/debug.h"

#endif
