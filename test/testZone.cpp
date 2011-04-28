/**
 * This code is part of libcity library.
 *
 * @file test/testZone.cpp
 * @date 26.04.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @brief Unit test of Zone class
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
#include "../src/area/zone.h"
#include "../src/geometry/polygon.h"
#include "../src/debug.h"

SUITE(ZoneClass)
{
  TEST(Empty)
  {
  }
}