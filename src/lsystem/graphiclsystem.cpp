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
  // FIXME throw exception
  cursor = cursorStack.back();
  cursorStack.pop_back();
}

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
  if (graphicInformationForSymbols->find(symbol) == graphicInformationForSymbols->end())
  {
    (*graphicInformationForSymbols)[symbol] = new GraphicInformation();
  }

  (*graphicInformationForSymbols)[symbol]->cursorAfterInterpretation = cursor;
}

void GraphicLSystem::removeSymbol(SymbolString::iterator position)
{
  delete (*graphicInformationForSymbols)[*position];
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
    int rewritesMade = doIterations(1);

    if (rewritesMade > 0)
    {
      return readNextSymbol();
    }

    return '\0';
  }
  else
  {
//     debug("Interpreting: " << currentSymbol->getSymbol());
//     debug("  Position before: " << cursor.getPosition().toString());
//     debug("  Direction before: " << cursor.getDirection().toString());
    currentlyInterpretedSymbol = position;
    interpretSymbol(currentSymbol->getSymbol());
    currentSymbol->markAsRead();
//     debug("  Position after: " << cursor.getPosition().toString());
//     debug("  Direction after: " << cursor.getDirection().toString());
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
    default:
      /* do nothing */
      break;
  }
}

void GraphicLSystem::setInitialPosition(Point const& position)
{
  cursor.setPosition(position);
}

void GraphicLSystem::setInitialDirection(Vector const& direction)
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

GraphicLSystem::Cursor::Cursor(Point const& inputPosition, Vector const& inputDirection)
  : position(0), direction(0)
{
  position  = new Point(inputPosition);
  direction = new Vector(inputDirection);
}

GraphicLSystem::Cursor::Cursor(Cursor const& source)
{
  position  = new Point(0,0,0);
  direction = new Vector(0,0,0);

  *position  = source.getPosition();
  *direction = source.getDirection();
}


GraphicLSystem::Cursor& GraphicLSystem::Cursor::operator=(Cursor const& source)
{
  *position  = source.getPosition();
  *direction = source.getDirection();

  return *this;
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

void GraphicLSystem::Cursor::setPosition(Point const& newPosition)
{
  *position = newPosition;
}

void GraphicLSystem::Cursor::setDirection(Vector const& newDirection)
{
  *direction = newDirection;
  direction->normalize();
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
