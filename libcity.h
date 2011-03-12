/**
 * This code is part of libcity library.
 *
 * @file geometry/curve.h
 * @date 19.02.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @brief Representation of curve
 *
 */

class Point;

class Curve
{
  public:
    Curve();
    ~Curve();

  private:
    Point *begining;
    Point *end;
};/**
 * This code is part of libcity library.
 *
 * @file geometry/line.h
 * @date 19.02.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @brief Representation of a line segment
 *
 */

#ifndef _LINE_H_
#define _LINE_H_

class Point;

class Line
{
  public:
    Line();
    Line(Point first, Point second);

    ~Line();

  private:
    Point *begining;
    Point *end;
};

#endif
/**
 * This code is part of libcity library.
 *
 * @file geometry/point.h
 * @date 19.02.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @brief Point in 3D space. But can also represent 2D and 1D points.
 *
 */

#ifndef _POINT_H_
#define _POINT_H_

class Point
{
  public:
    Point(); /**< [0,0,0] */
    Point(int x, int y); /**< 2D */
    Point(int x, int y, int z); /**< 3D */

    ~Point();

  private:
    int xPosition;
    int yPosition;
    int zPosition;

  public:
    int x() const;
    int y() const;
    int z() const; /**< Undefined in 2D. */

    void setX(int coordinate);
    void setY(int coordinate);
    void setZ(int coordinate);

    bool operator==(Point &second);
};


inline int Point::x() const
{
  return xPosition;
}

inline int Point::y() const
{
  return yPosition;
}

inline int Point::z() const
{
  return zPosition;
}

inline void Point::setX(int coordinate)
{
  xPosition = coordinate;
}

inline void Point::setY(int coordinate)
{
  yPosition = coordinate;
}

inline void Point::setZ(int coordinate)
{
  zPosition = coordinate;
}

#endif/**
 * This code is part of libcity library.
 *
 * @file units.h
 * @date 19.02.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @brief Definition of units for geometry
 *
 */

namespace libcity
{
  /* Basic unit for the whole library (in pixels). */
  const int METER  = 100;
  const int METERS = METER;
};/**
 * This code is part of libcity library.
 *
 * @file geometry/vector.h
 * @date 05.03.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @brief Vector in 3D space. But can also represent 2D and 1D vectors.
 *
 */

#ifndef _VECTOR_H_
#define _VECTOR_H_

class Vector
{
  public:
    Vector(); /**< [0,0,0] */
    Vector(double x); /**< 1D */
    Vector(double x, double y); /**< 2D */
    Vector(double x, double y, double z); /**< 3D */

    ~Vector();

  private:
    double xDirection;
    double yDirection;
    double zDirection;

  public:
    double x() const;
    double y() const;
    double z() const; /**< Undefined in 2D. */

    void setX(double coordinate);
    void setY(double coordinate);
    void setZ(double coordinate);

    void rotateAroundX(double degrees);
    void rotateAroundY(double degrees);
    void rotateAroundZ(double degrees);

    void normalize();

    bool operator==(Vector &second);
    Vector operator*(double &constant);
    Vector operator/(double &constant);
    Vector operator+(Vector &vector);

};
#endif/**
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
/**
 * This code is part of libcity library.
 *
 * @file lsystem/lsystem.h
 * @date 05.03.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @brief Base class for string based L-system rewriting engine.
 *
 * LSystem class is a base for another L-System driven classes.
 * It works with strings to achive maximal complexity of the
 * code (even though it's not optimal).
 *
 * Implementation of this L-System is context-free and deterministic.
 * Stochastic behavior can be achieved as well (@see LSystem::ProductionRule).
 */

#ifndef _LSYSTEM_H_
#define _LSYSTEM_H_

#include <set>
#include <map>
#include <list>
#include <string>

class LSystem
{
  public:
    LSystem();
    virtual ~LSystem();

    /** Production rule of a LSystem.
        With one successor it's a deterministic rule,
        with more successors it's stochastic rule with a
        1/number_of_successors chance of occurence. */
    class ProductionRule
    {
      public:
        ProductionRule();
        ProductionRule(char leftSide, std::string rightSide);

        char predecessor();
        std::string successor();
        void addSuccessor(std::string rightSideString);

      private:
        char leftSide;
        std::list<std::string> rightSide;
    };

    void setIterations(int numberOfIterations);

    void newRule(char predecessor, std::string successor);

    std::string producedString();

  protected:
    std::set<char> alphabet; /**< Finite set of symbols */
    std::string axiom; /**< Initial string */

    /** Production rules are stored in std::map.
        Stochastic rules have more than one successor.
        Which one is used is determined randomly within
        the rule. @see LSystem::ProductionRule */
    std::map<char, ProductionRule> rules;

    int iterations;

    std::list<char> outputString; /**< Produced string */

    std::list<char>::iterator currentPosition;

    void doSingleIteration();
    void rewrite();
    void rewrite(std::list<char>::iterator position);

  private:
    bool isResultReady;
};

#endif
/**
 * This code is part of libcity library.
 *
 * @file lsystem/lsystemstring.h
 * @date 10.03.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @brief FIXME
 */

#ifndef _LSYSTEMSTRING_H_
#define _LSYSTEMSTRING_H_

#include <list>

class LSystemSymbol;

class LSystemString : public std::list<LSystemSymbol*>
{
  public:
    LSystemString();

//     void rewrite(Parent::Iterator position, LSystemString);
};

#endif
/**
 * This code is part of libcity library.
 *
 * @file lsystem/roadlsystem.h
 * @date 12.03.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @brief Base class for Road generators
 *
 * @see LSystem
 * @see GraphicsLSystem
 *
 */

#ifndef _ROADLSYSTEM_H_
#define _ROADLSYSTEM_H_

#include "graphiclsystem.h"

class RoadLSystem : public GraphicLSystem
{
  public:
    RoadLSystem();
    virtual ~RoadLSystem();

    void setPosition(Point position);
    void setDirection(Vector direction);
  protected:

};

#endif
/**
 * This code is part of libcity library.
 *
 * @file lsystem/symbols.h
 * @date 10.03.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @brief Symbols used in LSystem
 *
 * Set of symbols, that can be used in LSystem. This
 * architecture was chosen, because it's extensibility.
 * Another symbols can be easily added, parameters
 * can be modified and much more functionality added.
 */

#ifndef _SYMBOLS_H_
#define _SYMBOLS_H_

#include <set>
#include <map>
#include <list>
#include <string>

class LSystemSymbol
{
  public:
    enum definedSymbols
    {
      PUSH_POSITION = '[',
      POP_POSITION  = ']',
      DRAW_LINE     = 'L',
      DRAW_POINT    = 'P',
      TURN_ANGLE    = 'T',
      MOVE_FORWARD  = 'M'
    };

    LSystemSymbol();
    virtual ~LSystemSymbol();

    char getSymbol();

    bool operator==(char character);
    bool operator==(LSystemSymbol another);

  protected:
    char symbol;
};

class GenericSymbol : public LSystemSymbol
{
  public:
    GenericSymbol(char identifier);
};

/* Graphical symbols */
class DrawLineSymbol : public LSystemSymbol
{
  public:
    DrawLineSymbol(double distance, char identifier = LSystemSymbol::DRAW_LINE);

  private:
    double distance;
};

class TurnAngleSymbol : public LSystemSymbol
{
  public:
    TurnAngleSymbol(double angle, char identifier = LSystemSymbol::TURN_ANGLE);

  private:
    double angle;
};

#endif
/**
 * This code is part of libcity library.
 *
 * @file streetgraph/intersection.h
 * @date 02.03.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @brief Intersection of N roads
 *
 *
 */

#ifndef _INTERSECTION_H_
#define _INTERSECTION_H_

#include <list>

class Point; //!< From geometry package
class Road;

class Intersection
{
  private:
    Intersection();

  public:
    Intersection(Point coordinates);

    ~Intersection();

    Point position() const;
    void  setPosition(Point coordinates);

    int  numberOfWays() const; /**< Number of ways of the intersection */
    void addRoad(Road* road) throw();

  private:
    std::list<Road*> *roads;     /**< Topological information */
    Point *geometrical_position; /**< Geometrical information */
};


#endif
/**
 * This code is part of libcity library.
 *
 * @file streetgraph/intersection.h
 * @date 02.03.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @brief Base class for road representation
 *
 */

#ifndef _ROAD_H_
#define _ROAD_H_

class Line;
class Intersection;

class Road
{
  private:
    Road();

  public:
    /** Create road between two intersections.
        Path is determined automaticaly.*/
    Road(Intersection *first, Intersection *second);
    virtual ~Road();

    Intersection* begining() const;
    Intersection* end() const;

    void setBegining(Intersection* intersection);
    void setEnd(Intersection* intersection);

    Line* path() const;

    void setPath(Line& roadPath) throw();

  private:
    /* Topological information */
    Intersection* from; /**< Where the road starts. */
    Intersection* to;   /**< Where it leads to. */

    /* Geometrical information */
    Line* geometrical_path; /**< Path that the road takes between the two topological points */

    void estimatePath();
};

/* Inlines */

inline Intersection* Road::begining() const
{
  return from;
}

inline Intersection* Road::end() const
{
  return to;
}

inline void Road::setBegining(Intersection* intersection)
{
  from = intersection;
}

inline void Road::setEnd(Intersection* intersection)
{
  to = intersection;
}

inline Line* Road::path() const
{
  return geometrical_path;
}


#endif
/**
 * This code is part of libcity library.
 *
 * @file streetgraph.h
 * @date 17.02.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @brief Street graph representation
 *
 * Roads and Intersections form together an undirected
 * plannar graph. There are two levels of the graph.
 *
 * On a *topological* level, the streetgraph says where
 * a certain road begins and where it leads to.
 * On the lower level, the *geometrical* level, the graph
 * says where exactly in the space are the topological
 * elements (Intersection, Roads) located by specifying
 * position (Point) for an intersection and path (Line)
 * for a road.
 *
 */

#ifndef _STREETGRAPH_H_
#define _STREETGRAPH_H_

#include <list>

class Intersection;
class Road;
class Point;

class StreetGraph
{
  public:
    StreetGraph();
    ~StreetGraph();

    void addPrimaryRoad(Point from, Point to);
    void addSecondaryRoad(Point from, Point to);

  private:
    /** All intersections in the street graph. */
    std::list<Intersection> *intersections;

    /** All roads in the street graph.
        This is not neccessary, but could be
        useful. */
    std::list<Road> *roads;
};

#endif/**
 * This code is part of libcity library.
 *
 * @file streetgraph/zone.h
 * @date 2.03.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @brief !!! NOT SURE YET
 *
 */

#ifndef _ZONE_H_
#define _ZONE_H_

#endif