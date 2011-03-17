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
#include "../debug.h"

/* ************************** */
/* *** LSystem IMPLEMENTATION */
LSystem::LSystem()
{
  producedString = new SymbolString;
  initialize();
}

LSystem::~LSystem()
{

  freeProducedString();
}

void LSystem::freeProducedString()
{
  while(!producedString->empty())
  {
    removeSymbol(--producedString->end());
  }
  delete producedString;
}

void LSystem::removeSymbol(SymbolString::iterator symbolPosition)
{
  Symbol *removedSymbol = *symbolPosition;
  producedString->erase(symbolPosition);
  delete removedSymbol;
}

void LSystem::setAlphabet(std::string alphabetCharacters)
{
  initialize();

  for (std::string::iterator position = alphabetCharacters.begin();
       position != alphabetCharacters.end();
       position++)
  {
    alphabet.insert(*position);
  }
}

void LSystem::addToAlphabet(std::string alphabetCharacters)
{
  for (std::string::iterator position = alphabetCharacters.begin();
       position != alphabetCharacters.end();
       position++)
  {
    alphabet.insert(*position);
  }
}

void LSystem::initialize()
{
  alphabet.clear();
  axiom = "";
  rules.clear();
  producedString->clear();
}

void LSystem::reset()
{
  producedString->clear();

  for (std::string::iterator position = axiom.begin();
       position != axiom.end();
       position++)
  {
    producedString->push_back(new Symbol(*position));
  }
}

void LSystem::setAxiom(std::string startingSequence)
{
  if (startingSequence == "" || !isInAlphabet(startingSequence))
  {
    // FIXME throw exception
  }

  axiom = startingSequence;
  reset();
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
    position++;
  }

  return true;
}

bool LSystem::isTerminal(char character) const
{
  return rules.find(character) == rules.end();
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

void LSystem::doIteration()
{
  SymbolString::iterator position = producedString->begin();
  SymbolString::iterator nextPosition;

  while (position != producedString->end())
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

void LSystem::doIterations(int howManyIterations)
{
  for (int iteration = 0; iteration < howManyIterations; iteration++)
  {
    doIteration();
  }
}

void LSystem::rewrite(SymbolString::iterator position)
{
  Symbol predecessor = **position;
  std::string successor;

  if (rules.find(predecessor) != rules.end())
  /* Not a constant symbol */
  {
    successor = rules[predecessor].successor();

    /* Insert the successor before the character at position */
    for (std::string::iterator character = successor.begin();
         character != successor.end();
         character++)
    {
      producedString->insert(position, new Symbol(*character));
    }

    /* And remove the rewrited character from the string */
    removeSymbol(position);
  }
  else
  /* Constant symbol, do nothing. */
  {}
}

std::string LSystem::getProducedString()
{
  std::string outputString;
  outputString.clear();
  for (SymbolString::const_iterator position = producedString->begin();
       position != producedString->end();
       position++)
  {
    outputString.push_back((*position)->getSymbol());
  }
  return outputString;
}

void LSystem::debugDumpProducedStringAddresses()
{
  int counter = 0;
  debug("SymbolString address dump:");
  for (SymbolString::const_iterator position = producedString->begin();
       position != producedString->end();
       position++)
  {
    debug("  " << counter << ": " << *position);
    counter++;
  }
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