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

class Point;

class Polygon
{
  public:
    Polygon(); /**< Empty polygon */
    Polygon(Point const& one, Point const& two, Point const& three); /**< Triangle */
    Polygon(Point const& one, Point const& two, Point const& three, Point const& four); /**< Rectangle */

    ~Polygon();

  private:
    std::vector<Point*> *vertices;

  public:
    Point vertex(unsigned int number) const;

    unsigned int numberOfVertices() const;

    void addVertex(Point const& vertex);
    void removeVertex(unsigned int number);

    /** Works ONLY in 2D !!! */
    double area() const;

    /** Works ONLY in 2D !!! */
    Point centroid() const;

    bool encloses2D(Point const& point) const;

    bool isSubAreaOf(Polygon const& biggerPolygon);
    bool operator==(Polygon const& second);

  private:
    void initialize();
    void freeVertices();

    double signedArea() const;
};

#endif