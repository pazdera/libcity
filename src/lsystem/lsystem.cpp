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

/* ************************** */
/* *** LSystem IMPLEMENTATION */
LSystem::LSystem()
  : axiom(""), rules(), producedString()
{}

LSystem::~LSystem()
{}

void LSystem::setAxiom(std::string startingSequence)
{
  if (startingSequence == "" || !isInAlphabet(startingSequence))
  {
    // FIXME throw exception
  }

  axiom = startingSequence;

  producedString.clear();
  for (std::string::iterator position = axiom.begin();
       position != axiom.end();
       position++)
  {
    producedString.push_back(Symbol(*position));
  }
}

bool LSystem::isInAlphabet(char checkedCharacter) const
{
  return alphabet.find(checkedCharacter) != alphabet.end();
}

bool LSystem::isInAlphabet(std::string checkedString) const
{
  std::string::iterator position = checkedString.begin();
  while (position != checkedString.end())
  /* Iterate through the whole string and check all the characters */
  {
    if (!isInAlphabet(*position))
    {
      return false;
    }
  }

  return true;
}

void LSystem::addRule(char predecessor, std::string successor)
{
  if (!isInAlphabet(predecessor) || !isInAlphabet(successor))
  {
    //FIXME throw exception
  }

  std::map<char, ProductionRule>::iterator existingRule = rules.find(predecessor);
  if (existingRule != rules.end())
  /* Rule with the same left side already exists */
  {
    existingRule->second.addSuccessor(successor);
  }
  else
  /* Create new rule */
  {
    rules[predecessor] = ProductionRule(predecessor, successor);
  }
}

void LSystem::doNextIteration()
{
  std::list<Symbol>::iterator position = producedString.begin();
  std::list<Symbol>::iterator nextPosition;

  while (position != producedString.end())
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

void LSystem::rewrite(std::list<Symbol>::iterator position)
{
  Symbol predecessor = *position;
  std::string successor;

  if (rules.find(predecessor) != rules.end())
  /* Not a constant symbol */
  {
    successor = rules[predecessor].successor();

    /* Insert the successor before the character at position */
    producedString.insert(position, successor.begin(), successor.end());

    /* And remove the rewrited character from the string */
    producedString.erase(position);
  }
  else
  /* Constant symbol, do nothing. */
  {}
}

std::string LSystem::getProducedString() const
{
  std::string output;
  for (std::list<Symbol>::const_iterator position = producedString.begin();
       position != producedString.end();
       position++)
  {
    output += *position;
  }

  return output;
}

/* ********************************* */
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

char LSystem::ProductionRule::predecessor() const
{
  return leftSide;
}

std::string LSystem::ProductionRule::successor() const
{
  // FIXME: Must return RANDOM successor not the FIRST one!
  return rightSide.front();
}

/* ********************* */
/* Symbol IMPLEMENTATION */
LSystem::Symbol::Symbol(char character)
  : symbol(character)
{}

LSystem::Symbol::~Symbol()
{}

bool LSystem::Symbol::isMarkedRead() const
{
  return alreadyRead;
}

LSystem::Symbol::operator char() const
{
  return symbol;
}

bool LSystem::Symbol::operator==(char character) const
{
  return symbol == character;
}

bool LSystem::Symbol::operator==(Symbol another) const
{
  return (char)another == symbol;
}


void LSystem::Symbol::markAsRead()
{
  alreadyRead = true;
}

char LSystem::Symbol::getSymbol() const
{
  return symbol;
}