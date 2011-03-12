/**
 * This code is part of libcity library.
 *
 * @file lsystem/graphiclsystem.h
 * @date 05.03.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @brief Extension of LSystem for general graphical application
 *
 * @see LSystem
 *
 * To the normal functionality of an LSystem this class adds
 *  - a drawing cursor and a cursor stack
 *  - possibillity of area constraints
 *  - defines some basic symbols of the drawing alphabet
 *     - draw line of a certain length
 *     - turn the cursor a certain angle
 *     - push the cursor's position on stack
 *     - pop the cursor's position from stack
 */

#ifndef _GRAPHICLSYSTEM_H_
#define _GRAPHICLSYSTEM_H_

#include <vector>

#include "lsystem.h"

class Point;
class Vector;

class GraphicLSystem : public LSystem
{
  public:
    GraphicLSystem();
    virtual ~GraphicLSystem();

  protected:
    void setAxiom(std::string startingSequence, Point startingPosition, Vector startingDirection);

    void pushCursor();
    void popCursor(); /** Does nothing when the stack is empty */

    Point  currentPosition();
    Vector currentDirection();
  private:
    /* Drawing cursor */
    Point*  cursorPosition;
    Vector* cursorDirection;
    std::vector< std::pair<Point*,Vector*> > cursorStack;

    void moveCursorOneStep();

    void defineAlphabet();
};

#endif
