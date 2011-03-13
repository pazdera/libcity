/**
 * This code is part of libcity library.
 *
 * @file point.class.test.h
 * @date 23.02.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @brief Unit test of Point class
 *
 * Unit test is a class derived from Unit. It's defined
 * inline in the declaration.
 */

// Includes
#include <string>
#include <iostream>

#include <stdlib.h>
#include <assert.h>

// Modules
#include "../unit.h"
#include "../../src/geometry/point.h"

class PointClassTest : public Unit
{
  public:
    PointClassTest()
      : Unit("Point class")
    {}

  private:
//     bool 

  public:
    bool run()
    {
      return true;
    }
};