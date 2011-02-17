/**
 * This code is part of libcity library.
 *
 * @file unit.h
 * @date 17.02.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @brief Base class for unit tests.
 *
 */

// Includes
#include <string>
#include <iostream>

#include <stdlib.h>
#include <assert.h>

// Modules

class Unit
{
  public:
    Unit();
    virtual ~Unit();

  private:
    int testCount;
    std::string currentTest;

    void printMessage(std::string message);
  protected:
    bool status;

    void startTest(std::string name);
    void finishTest();

  public:
    virtual bool run();
};