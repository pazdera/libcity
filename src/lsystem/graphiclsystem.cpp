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

#include "../debug.h"
#include "../geometry/point.h"
#include "../geometry/vector.h"

GraphicLSystem::GraphicLSystem()
  : LSystem(), cursor(), graphicInformationForSymbols(0)
{
  graphicInformationForSymbols = new std::map<Symbol*, GraphicInformation*>;

  /* Symbols:
   *  [ - push current position
   *  ] - pop current position
   *  . - draw point
   *  _ - draw line forward FIXME of what length?
   */
  setAlphabet("[]._");

  // FIXME set axiom and copy it to producedString
  setAxiom(".");
}

GraphicLSystem::~GraphicLSystem()
{
  freeGraphicInformation();
}

void GraphicLSystem::freeGraphicInformation()
{
  for (std::map<Symbol*, GraphicInformation*>::iterator position = graphicInformationForSymbols->begin();
       position != graphicInformationForSymbols->end();
       position++)
  {
    delete position->second;
  }

  delete graphicInformationForSymbols;
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

void GraphicLSystem::drawLine()
{}

void GraphicLSystem::drawPoint()
{}

void GraphicLSystem::loadCursorPositionForSymbol(Symbol *symbol)
{
  if (graphicInformationForSymbols->find(symbol) == graphicInformationForSymbols->end())
  {
    (*graphicInformationForSymbols)[symbol] = new GraphicInformation();
  }

  cursor = (*graphicInformationForSymbols)[symbol]->cursorAfterInterpretation;
}

void GraphicLSystem::saveCursorPositionForSymbol(Symbol *symbol)
{
  (*graphicInformationForSymbols)[symbol] = new GraphicInformation;
  (*graphicInformationForSymbols)[symbol]->cursorAfterInterpretation = cursor;
}

void GraphicLSystem::removeSymbol(SymbolString::iterator position)
{
  graphicInformationForSymbols->erase(*position);
  LSystem::removeSymbol(position);
}

char GraphicLSystem::readNextSymbol()
{
  if (producedString->empty())
  /* Should not happen */
  {
    return '\0';
  }

  SymbolString::iterator position = producedString->begin();
  Symbol *currentSymbol;
  while(position != producedString->end())
  /* Seek first unread symbol. */
  {
    currentSymbol = *position;
    if (!currentSymbol->isMarkedRead())
    {
      break;
    }
    else
    {
      loadCursorPositionForSymbol(currentSymbol);
      position++;
    }
  }

  if (position == producedString->end())
  /* If all symbols have been already read, generate some more. */
  {
    doIterations(1);
    return readNextSymbol();
  }
  else
  {
    interpretSymbol(currentSymbol->getSymbol());
    currentSymbol->markAsRead();
    saveCursorPositionForSymbol(currentSymbol);

    return currentSymbol->getSymbol();
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
    case '.':
      drawPoint();
      break;
    case '_':
      drawLine();
      break;
    default:
      /* do nothing */
      break;
  }
}

void GraphicLSystem::setInitialPosition(Point position)
{
  cursor.setPosition(position);
}

void GraphicLSystem::setInitialDirection(Vector direction)
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
  newDirection.normalize();
  *direction = newDirection;
}

void GraphicLSystem::Cursor::move(double distance)
{
  direction->normalize();
  position->setX(position->x() + direction->x()*distance);
  position->setY(position->y() + direction->y()*distance);
  position->setZ(position->z() + direction->z()*distance);
}

void GraphicLSystem::Cursor::turn(double angle)
{
  direction->rotateAroundZ(angle);
  direction->normalize();
}
