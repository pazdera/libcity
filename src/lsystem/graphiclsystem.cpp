/**
 * This code is part of libcity library.
 *
 * @file lsystem/graphiclsystem.cpp
 * @date 07.03.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @see graphiclsystem.h
 *
 */

#include "graphiclsystem.h"

GraphicLSystem::GraphicLSystem()
  : LSystem(), cursorPosition(), cursorDirection()
{
  defineAlphabet();
}

void GraphicLSystem::defineAlphabet()
{
  alphabet.insert('['); //! Push current position
  alphabet.insert(']'); //! Pop current position

  alphabet.insert('D'); //! Draw line of a random length

  alphabet.insert('L'); //! Turn left 90 degrees
  alphabet.insert('R'); //! Turn right 90 degrees
}

GraphicLSystem::~GraphicLSystem()
{
  
}