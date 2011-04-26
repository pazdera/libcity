/**
 * This code is part of libcity library.
 *
 * @file geometry/polygon.h
 * @date 19.03.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @brief 2D Polygon representation
 *
 */

#ifndef _POLYGON_H_
#define _POLYGON_H_

#include <vector>
#include <string>

class Point;
class Vector;
class LineSegment;

class Polygon
{
  public:
    Polygon(); /**< Empty polygon */
    Polygon(Point const& one, Point const& two, Point const& three); /**< Triangle */
    Polygon(Point const& one, Point const& two, Point const& three, Point const& four); /**< Rectangle */

    Polygon(Polygon const& source);
    Polygon& operator=(Polygon const& source);

    ~Polygon();

  private:
    std::vector<Point*> *vertices;

  public:
    Point vertex(unsigned int number) const;
    LineSegment edge(unsigned int number) const;

    unsigned int numberOfVertices() const;

    void addVertex(Point const& vertex);
    void updateVertex(unsigned int number, Point const& vertex);
    void removeVertex(unsigned int number);
    void clear();

    /** Works ONLY in 2D !!! */
    double area() const;

    /** Works ONLY in 2D !!! */
    Point centroid() const;

    /**
      Get normal vector of a certain edge. The
      vector ALWAYS points inside the polygon.

     @param[in] edgeNumber Number of the edge. Edges are numbered from 0
                           to numberOfVertices() - 1.
     @return Normalized normal vector.
      */
    Vector edgeNormal(unsigned int edgeNumber);

    /**
      Get normal vector to the plane this polygon makes.

     @return Normalized normal vector.
      */
    Vector normal();

    bool encloses2D(Point const& point) const;

    bool isSubAreaOf(Polygon const& biggerPolygon);
    bool operator==(Polygon const& second);

    std::string toString();
  private:
    void initialize();
    void freeVertices();

    double signedArea() const;
};

#endif