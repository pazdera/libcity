/**
 * This code is part of libcity library.
 *
 * @file lsystem/lsystem.cpp
 * @date 05.03.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @see lsystem.h
 *
 */

#include "lsystem.h"

LSystem::LSystem()
  : axiom(""), rules(), iterations(0), outputString()
{}

LSystem::~LSystem()
{}

void LSystem::doSingleIteration()
{
  std::list<char>::iterator position = outputString.begin();
  std::list<char>::iterator nextPosition;

  while (position != outputString.end())
  {
    /* Save the iterator for the next character, because
       the list can change and we don't want to expand
       the new parts in this iteration */
    nextPosition = position;
    nextPosition++;

    rewrite(position);

    position = nextPosition;
  }
}

void LSystem::rewrite(std::list<char>::iterator position)
{
  char predecessor = *position;
  std::string successor;

  if (rules.find(predecessor) != rules.end())
  /* Not a constant symbol */
  {
    successor = rules[predecessor].successor();

    /* Insert the successor before the character at position */
    outputString.insert(position, successor.begin(), successor.end());

    /* And remove the rewrited character from the string */
    outputString.erase(position);
  }
  else
  /* Constant symbol, do nothing. */
  {}
}

/* *** ProductionRule IMPLEMENTATION */
LSystem::ProductionRule::ProductionRule()
  : leftSide(0), rightSide()
{}

LSystem::ProductionRule::ProductionRule(char leftSideSymbol, std::string rightSideString)
{
  leftSide = leftSideSymbol;
  rightSide.push_back(rightSideString);
}

void LSystem::ProductionRule::addSuccessor(std::string rightSideString)
{
  rightSide.push_back(rightSideString);
}

char LSystem::ProductionRule::predecessor()
{
  return leftSide;
}

std::string LSystem::ProductionRule::successor()
{
  // FIXME: Must return RANDOM successor not the FIRST one!
  return rightSide.front();
}