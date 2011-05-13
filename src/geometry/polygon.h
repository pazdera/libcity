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
#include <list>

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
    Vector normal() const;

    /**
      Rotate polygon around its centroid by amount of degrees
      specified by the parameters.
     @remarks
       Uses centroid method, so it's not safe when the polygon
       is not in the XY plane.
     @note
       Positive amount of degrees is rotation counterclock-wise.
       Negative is clockwise.
     @param[in] xDegrees Amount of degrees to rotate in X.
     @param[in] yDegrees Amount of degrees to rotate in Y.
     @param[in] zDegrees Amount of degrees to rotate in Z.
     */
    void rotate(double xDegrees, double yDegrees, double zDegrees);

    /**
      Scale polygon by specified factor.
     @note
       The expansion is computed from polygon's centroid.
     @param[in] factor The scale factor. Passing number <= 0 will result in unspecified behavior.
     */
    void scale(double factor);

    /**
      Substract distance from the polygon's borders.
     @param[in] distance Distance to be substracted
     */
    void substract(double distance);
    
    /**
      Substract distance just from a single edge.
     @param[in] i Edge index
     @param[in] distance Distance to be substracted
     */
    void substractEdge(int edgeNumber, double distance);

    std::list<Polygon*> split(LineSegment const& splitLine);

    bool encloses2D(Point const& point) const;

    bool isNonSelfIntersecting();

    Polygon getBoundingRectangle();

    std::vector<Point> triangulate();
    std::vector<int> getSurfaceIndexes();

    bool isSubAreaOf(Polygon const& biggerPolygon);
    bool operator==(Polygon const& second);

    std::string toString() const;
  private:
    void initialize();
    void freeVertices();

    double signedArea() const;

    /* Helper functions for split polygon */
    bool isVertexIntersection(Point vertex, std::list<Point> intersections);
    bool areVerticesInPair(Point first, Point second, std::list<Point> intersections);

  private:
    /* Polygon triangulation */
    /* Taken from:
     * http://www.flipcode.com/archives/Efficient_Polygon_Triangulation.shtml */ 
    // triangulate a contour/polygon, places results in STL vector
    // as series of triangles.
    bool triangulation(std::vector<Point> *points, std::vector<int> *sequence);

    // decide if point Px/Py is inside triangle defined by
    // (Ax,Ay) (Bx,By) (Cx,Cy)
    bool isInsideTriangle(double Ax, double Ay,
                        double Bx, double By,
                        double Cx, double Cy,
                        double Px, double Py);

    bool snip(int u,int v,int w,int n,int *V);
};

#endif