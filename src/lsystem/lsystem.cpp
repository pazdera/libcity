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
#include "../random.h"

/* ************************** */
/* *** LSystem IMPLEMENTATION */
LSystem::LSystem()
{
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

void LSystem::setAlphabet(std::string const& alphabetCharacters)
{
  freeProducedString();
  initialize();

  for (std::string::const_iterator position = alphabetCharacters.begin();
       position != alphabetCharacters.end();
       position++)
  {
    alphabet.insert(*position);
  }
}

void LSystem::addToAlphabet(std::string const& alphabetCharacters)
{
  for (std::string::const_iterator position = alphabetCharacters.begin();
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
  producedString = new SymbolString;
}

void LSystem::reset()
{
  freeProducedString();
  producedString = new SymbolString;

  for (std::string::iterator position = axiom.begin();
       position != axiom.end();
       position++)
  {
    producedString->push_back(new Symbol(*position));
  }
}

void LSystem::setAxiom(std::string const& startingSequence)
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

bool LSystem::isInAlphabet(std::string const& checkedString) const
{
  std::string::const_iterator position = checkedString.begin();
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

void LSystem::addRule(char predecessor, std::string const& successor)
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

int LSystem::doIteration()
{
  SymbolString::iterator position = producedString->begin();
  SymbolString::iterator nextPosition;

  int rewritesMade = 0;

  while (position != producedString->end())
  {
    /* Save the iterator for the next character, because
       the list can change and we don't want to expand
       the new parts in this iteration */
    nextPosition = position;
    nextPosition++;

    if (!isTerminal((*position)->getSymbol()))
    {
      rewritesMade++;
      rewrite(position);
    }

    position = nextPosition;
  }

  return rewritesMade;
}

int LSystem::doIterations(int howManyIterations)
{
  int rewritesMade = 0;
  for (int iteration = 0; iteration < howManyIterations; iteration++)
  {
    rewritesMade += doIteration();
  }

  return rewritesMade;
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

LSystem::ProductionRule::ProductionRule(char leftSideSymbol, std::string const& rightSideString)
{
  leftSide = leftSideSymbol;
  rightSide.push_back(rightSideString);
}

void LSystem::ProductionRule::addSuccessor(std::string const& rightSideString)
{
  rightSide.push_back(rightSideString);
}

char LSystem::ProductionRule::predecessor() const
{
  return leftSide;
}

std::string LSystem::ProductionRule::successor() const
{
  Random generator;
  return rightSide[generator.generateInteger(0, rightSide.size() - 1)];
}

/* ********************* */
/* Symbol IMPLEMENTATION */
LSystem::Symbol::Symbol(char character)
  : symbol(character), alreadyRead(false)
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

bool LSystem::Symbol::operator==(Symbol const& another) const
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