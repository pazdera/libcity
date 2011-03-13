/**
 * This code is part of libcity library.
 *
 * @file main.cpp
 * @date 17.02.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * Main program for the unit tests.
 *
 */

#include "unit.h"

#include "units/point.class.test.cpp"
#include "units/vector.class.test.cpp"

int main()
{
  bool status = true;

  status = status && PointClassTest().run();
  status = status && VectorClassTest().run();
  return status;
}