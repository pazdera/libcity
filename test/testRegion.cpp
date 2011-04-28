/**
 * This code is part of libcity library.
 *
 * @file test/testRegion.cpp
 * @date 28.04.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @brief Unit test of Region class
 *
 * Unit tests require UnitTest++ framework! See README
 * for more informations.
 */

/* Include UnitTest++ headers */
#include <UnitTest++.h>

// Includes
#include <iostream>
#include <string>
#include <stdexcept>

// Tested modules
#include "../src/area/region.h"
#include "../src/geometry/polygon.h"
#include "../src/debug.h"

SUITE(RegionClass)
{
  TEST(Empty)
  {
  }
}