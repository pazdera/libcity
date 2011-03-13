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

#include "../geometry/point.h"
#include "../geometry/vector.h"

GraphicLSystem::GraphicLSystem()
  : LSystem(), cursor(), currentStringPosition()
{
  defineAlphabet();

  // FIXME set axiom and copy it to producedString
  currentStringPosition = producedString.begin();
}

GraphicLSystem::~GraphicLSystem()
{
}

void GraphicLSystem::defineAlphabet()
{
  alphabet.insert('['); //! Push current position
  alphabet.insert(']'); //! Pop current position

}

void GraphicLSystem::pushCursor()
{
  cursorStack.push_back(cursor);
}

void GraphicLSystem::popCursor()
{
  cursor = cursorStack.back();
  cursorStack.pop_back();
}

void GraphicLSystem::readNextSymbol()
{
  if (producedString.empty())
  /* Should not happen */
  {
    return;
  }

  if (currentStringPosition != producedString.end())
  /* We've reached the end */
  {
    doNextIteration();
    currentStringPosition = producedString.begin();
  }

  if (currentStringPosition->isMarkedRead())
  {
    currentStringPosition++;
    readNextSymbol();
  }
  else
  {
    interpretSymbol(currentStringPosition->getSymbol());
    currentStringPosition->markAsRead();
    currentStringPosition++;
  }
}

void GraphicLSystem::interpretSymbol(char symbol)
{
  switch (symbol)
  {
    case '[':
      pushCursor();
      break;
    case ']':
      popCursor();
      break;
    default:
      /* do nothing */
      break;
  }
}

void GraphicLSystem::setStartingPosition(Point position)
{
  cursor.setPosition(position);
}

void GraphicLSystem::setStartingDirection(Vector direction)
{
  cursor.setDirection(direction);
}

/* ********************* */
/* Cursor IMPLEMENTATION */
GraphicLSystem::Cursor::Cursor()
  : position(0), direction(0)
{
  position  = new Point(0,0,0);
  direction = new Vector(0,0,0);
}

GraphicLSystem::Cursor::Cursor(Point inputPosition, Vector inputDirection)
  : position(0), direction(0)
{
  position  = new Point(inputPosition);
  direction = new Vector(inputDirection);
}

GraphicLSystem::Cursor::Cursor(const Cursor& anotherCursor)
  : position(0), direction(0)
{
  position  = new Point(0,0,0);
  direction = new Vector(0,0,0);

  *position  = anotherCursor.getPosition();
  *direction = anotherCursor.getDirection();
}

GraphicLSystem::Cursor::~Cursor()
{
  delete position;
  delete direction;
}

Point GraphicLSystem::Cursor::getPosition() const
{
  return *position;
}

Vector GraphicLSystem::Cursor::getDirection() const
{
  return *direction;
}

void GraphicLSystem::Cursor::setPosition(Point newPosition)
{
  *position = newPosition;
}

void GraphicLSystem::Cursor::setDirection(Vector newDirection)
{
  *direction = newDirection;
}