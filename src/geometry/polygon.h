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
    Polygon(Point one, Point two, Point three); /**< Triangle */
    Polygon(Point one, Point two, Point three, Point four); /**< Rectangle */

    ~Polygon();

  private:
    std::vector<Point*> *vertices;

  public:
    Point vertex(unsigned int number);

    unsigned int numberOfVertices();

    void addVertex(Point vertex);
    void removeVertex(unsigned int number);

    /** Works ONLY in 2D !!! */
    double area();

    /** Works ONLY in 2D !!! */
    Point centroid();

    bool isSubAreaOf(Polygon biggerPolygon);
    bool operator==(Polygon &second);

  private:
    void initialize();
    void freeVertices();

    double signedArea();
    
};



#endif