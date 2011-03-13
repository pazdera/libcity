/**
 * This code is part of libcity library.
 *
 * @file debug.h
 * @date 13.03.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @brief Basic debuging tools
 *
 */

#ifndef __DEBUG_H_
#define __DEBUG_H_

#include <iostream>
#include <assert.h>

/* Debugging is ON */
#define DEBUG


#ifdef DEBUG
#define debug(x) std::cerr << "DEBUG: " << x << std::endl
#else
#define debug(x)
#endif


#endif/**
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
    Point(double x, double y); /**< 2D */
    Point(double x, double y, double z); /**< 3D */

    ~Point();

  private:
    double xPosition;
    double yPosition;
    double zPosition;

  public:
    double x() const;
    double y() const;
    double z() const; /**< Undefined in 2D. */

    void set(double xCoord, double yCoord, double zCoord = 0);
    void setX(double coordinate);
    void setY(double coordinate);
    void setZ(double coordinate);

    bool operator==(Point &second);
};


inline double Point::x() const
{
  return xPosition;
}

inline double Point::y() const
{
  return yPosition;
}

inline double Point::z() const
{
  return zPosition;
}

inline void Point::setX(double coordinate)
{
  xPosition = coordinate;
}

inline void Point::setY(double coordinate)
{
  yPosition = coordinate;
}

inline void Point::setZ(double coordinate)
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

  const int PI = 3.14159265;
}/**
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

    double length();

    void set(double xCoord, double yCoord, double zCoord = 0);
    void setX(double coordinate);
    void setY(double coordinate);
    void setZ(double coordinate);

    void rotateAroundX(double degrees);
    void rotateAroundY(double degrees);
    void rotateAroundZ(double degrees);

    void normalize();

    bool operator==(Vector second);
    Vector operator*(double constant);
    Vector operator/(double constant);
    Vector operator+(Vector vector);

};
#endif/**
 * This code is part of libcity library.
 *
 * @file debug.h
 * @date 13.03.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @brief Basic debuging tools
 *
 */

#ifndef __DEBUG_H_
#define __DEBUG_H_

#include <iostream>
#include <assert.h>

/* Debugging is ON */
#define DEBUG


#ifdef DEBUG
#define debug(x) std::cerr << "DEBUG: " << x << std::endl
#else
#define debug(x)
#endif


#endif/**
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

  const int PI = 3.14159265;
}/**
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

    double length();

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

    /* WARNING Will reset produced string to axiom  */
    void setStartingPosition(Point position);
    void setStartingDirection(Vector direction);

  protected:
    virtual void readNextSymbol();
    virtual void interpretSymbol(char symbol);

    void pushCursor();
    void popCursor(); /**< Does nothing when the stack is empty */

    /**
     * Represents a drawing cursor in the LSystem
     */
    class Cursor
    {
      public:
        Cursor();
        Cursor(Point inputPosition, Vector inputDirection);
        Cursor(const Cursor& anotherCursor);
        ~Cursor();

        Point  getPosition() const;
        Vector getDirection() const;

        void setPosition(Point newPosition);
        void setDirection(Vector newDirection);
      private:
        Point*  position;
        Vector* direction;
    };

    Cursor cursor; /**< Drawing cursor */
  private:
    std::list<Symbol>::iterator currentStringPosition;
    std::vector<Cursor> cursorStack; /**< Stack for pushing cursors */

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

    /**
     * WARNING: will delete producedString!
     */
    void setAxiom(std::string startingSequence);

    /**
     * Does one rewriting iteration on the productionString.
     * NOTICE might return number of rewrites done
     */
    void doNextIteration();

    /**
     * Adds a new rule to the LSystem. All the symbols in
     * the rule must be in the LSystem's alphabet.
     */
    void addRule(char predecessor, std::string successor);

    std::string getProducedString() const; /**< Returns the whole produced string */

  protected:
    /** Internal representation of production rule of a LSystem.
        With one successor it's a deterministic rule,
        with more successors it's stochastic rule with a
        1/number_of_successors chance of occurence. */
    class ProductionRule
    {
      public:
        ProductionRule();
        ProductionRule(char leftSide, std::string rightSide);

        char predecessor() const;
        std::string successor() const;
        void addSuccessor(std::string rightSideString);

      private:
        char leftSide;
        std::list<std::string> rightSide;
    };

    /** 
     * Internal representation of a symbol in a
     * LSystem. It's just a single character, but
     * extended to store various parameters.
     */
    class Symbol
    {
      public:
        Symbol(char character);
        virtual ~Symbol();

        void markAsRead();

        bool isMarkedRead() const;
        char getSymbol() const;

        operator char() const;
        bool operator==(char character) const;
        bool operator==(Symbol another) const;

      protected:
        char symbol;
        bool alreadyRead;
    };

    std::set<char> alphabet; /**< Finite set of symbols */
    std::string axiom; /**< Initial string */

    /** Production rules are stored in std::map.
        Stochastic rules have more than one successor.
        Which one is used is determined randomly within
        the rule. @see LSystem::ProductionRule */
    std::map<char, ProductionRule> rules;

    std::list<Symbol> producedString; /**< Produced string */

    /** 
     * Attempts to rewrite character specified by
     * the position iterator. */
    void rewrite(std::list<Symbol>::iterator position);

  private:
    bool isInAlphabet(char checkedCharacter) const; /**< Check if character is in this LSystem's alphabet */
    bool isInAlphabet(std::string checkedString) const; /**< Checks the whole string */
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

class Point;
class Vector;
class Road;

class RoadLSystem : public GraphicLSystem
{
  public:
    RoadLSystem();
    virtual ~RoadLSystem();

    Road* getNextIdealRoadSegment();

  protected:
    virtual void interpretSymbol(char symbol);

    void turnLeft90Degrees();
    void turnRight90Degrees();
  private:
    void defineAlphabet();
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

    /* WARNING Will reset produced string to axiom  */
    void setStartingPosition(Point position);
    void setStartingDirection(Vector direction);

  protected:
    virtual void readNextSymbol();
    virtual void interpretSymbol(char symbol);

    void pushCursor();
    void popCursor(); /**< Does nothing when the stack is empty */

    /**
     * Represents a drawing cursor in the LSystem
     */
    class Cursor
    {
      public:
        Cursor();
        Cursor(Point inputPosition, Vector inputDirection);
        Cursor(const Cursor& anotherCursor);
        ~Cursor();

        Point  getPosition() const;
        Vector getDirection() const;

        void setPosition(Point newPosition);
        void setDirection(Vector newDirection);
      private:
        Point*  position;
        Vector* direction;
    };

    Cursor cursor; /**< Drawing cursor */
  private:
    std::list<Symbol>::iterator currentStringPosition;
    std::vector<Cursor> cursorStack; /**< Stack for pushing cursors */

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

    /**
     * \WARNING: Will delete axiom and all rules
     */
    void setAlphabet(std::string alphabetCharacters);

    /**
     * \WARNING: Will delete producedString
     */
    void setAxiom(std::string startingSequence);

    /**
     * Does one rewriting iteration on the productionString.
     * NOTICE: Might return number of rewrites done
     */
    void doNextIteration();

    /**
     * Adds a new rule to the LSystem. All the symbols in
     * the rule must be in the LSystem's alphabet.
     */
    void addRule(char predecessor, std::string successor);

    std::string getProducedString() const; /**< Returns the whole produced string */

  protected:
    /** Internal representation of production rule of a LSystem.
        With one successor it's a deterministic rule,
        with more successors it's stochastic rule with a
        1/number_of_successors chance of occurence. */
    class ProductionRule
    {
      public:
        ProductionRule();
        ProductionRule(char leftSide, std::string rightSide);

        char predecessor() const;
        std::string successor() const;
        void addSuccessor(std::string rightSideString);

      private:
        char leftSide;
        std::list<std::string> rightSide;
    };

    /** 
     * Internal representation of a symbol in a
     * LSystem. It's just a single character, but
     * extended to store various parameters.
     */
    class Symbol
    {
      public:
        Symbol(char character);
        virtual ~Symbol();

        void markAsRead();

        bool isMarkedRead() const;
        char getSymbol() const;

        operator char() const;
        bool operator==(char character) const;
        bool operator==(Symbol another) const;

      protected:
        char symbol;
        bool alreadyRead;
    };

    std::set<char> alphabet; /**< Finite set of symbols */
    std::string axiom; /**< Initial string */

    /** Production rules are stored in std::map.
        Stochastic rules have more than one successor.
        Which one is used is determined randomly within
        the rule. @see LSystem::ProductionRule */
    std::map<char, ProductionRule> rules;

    std::list<Symbol> producedString; /**< Produced string */

    /** 
     * Attempts to rewrite character specified by
     * the position iterator. */
    void rewrite(std::list<Symbol>::iterator position);

  private:
    bool isInAlphabet(char checkedCharacter) const; /**< Check if character is in this LSystem's alphabet */
    bool isInAlphabet(std::string checkedString) const; /**< Checks the whole string */
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

class Point;
class Vector;
class Road;

class RoadLSystem : public GraphicLSystem
{
  public:
    RoadLSystem();
    virtual ~RoadLSystem();

    Road* getNextIdealRoadSegment();

  protected:
    virtual void interpretSymbol(char symbol);

    void turnLeft90Degrees();
    void turnRight90Degrees();
  private:
    void defineAlphabet();
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