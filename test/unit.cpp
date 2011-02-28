/**
 * This code is part of libcity library.
 *
 * @file unit.cpp
 * @date 17.02.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @see unit.h
 *
 */

// Header
#include "unit.h"

// Includes
#include <string>
#include <iostream>

#include <stdlib.h>

// Modules

Unit::Unit()
  : status(false)
{}

Unit::~Unit()
{}

void Unit::printMessage(std::string message)
{
  if (currentTest != "")
  {
    std::cerr << "\t" << message << std::endl;
  }
  else
  {
    std::cerr << message << std::endl;
  }
}

void Unit::startTest(std::string name)
{
  if (currentTest == "")
  {
    currentTest = name;
    testCount++;
    printMessage("TEST case \"" + name + "\" started.");
  }
  else
  {
    std::cerr << "Attempt to begin a new test case (" + name + ") without finishing the previous one (" + currentTest + ").";
    abort();
  }
}

void Unit::finishTest()
{
  if (currentTest != "")
  {
    printMessage("TEST case \"" + currentTest + "\" finished.");
    currentTest = "";
  }
  else
  {
    std::cerr << "No running test to finish.";
    abort();
  }
}
