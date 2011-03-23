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

    /* WARNING Will reset produced string to axiom  */
    void setInitialPosition(Point const& position);
    void setInitialDirection(Vector const& direction);

    virtual char readNextSymbol();

  protected:
    virtual void interpretSymbol(char symbol);

    void pushCursor();
    void popCursor(); /**< Does nothing when the stack is empty */
    virtual void drawLine();
    virtual void drawPoint();

    void loadCursorPositionForSymbol(Symbol *symbol);
    void saveCursorPositionForSymbol(Symbol *symbol);

    /** Removes graphic representation for symbol as well. */
    virtual void removeSymbol(SymbolString::iterator position);

    /**
     * Represents a drawing cursor in the LSystem
     */
    class Cursor
    {
      public:
        Cursor();
        Cursor(Point const& inputPosition, Vector const& inputDirection);

        Cursor(Cursor const& source);
        Cursor& operator=(Cursor const& source);

        ~Cursor();

        Point  getPosition() const;
        Vector getDirection() const;

        void setPosition(Point const& newPosition);
        void setDirection(Vector const& newDirection);

        void move(double distance);
        void turn(double angle);
      private:
        Point*  position;
        Vector* direction;
    };

    /**
     *  Additional graphic information stored for
     *  each symbol in SymbolString.
     */
    class GraphicInformation
    {
      public:
        Cursor cursorAfterInterpretation;
    };

    Cursor cursor; /**< Drawing cursor */
  private:
    std::map<Symbol*, GraphicInformation*>* graphicInformationForSymbols;
    void freeGraphicInformation();

    std::vector<Cursor> cursorStack; /**< Stack for pushing cursors */
};

#endif
