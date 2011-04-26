/**
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

/* STL */
#include <string>

class Point;

class Vector
{
  public:
    Vector(); /**< Initialize zero length vector (0,0,0). */
    Vector(double x); /**< One dimension only (1D). */
    Vector(double x, double y); /**< Two dimensions (2D). */
    Vector(double x, double y, double z); /**< Three dimensions (3D). */

    /** Initialize Vector from two points. */
    Vector(Point const& first, Point const& second);

       /* Not neccessary */
//     Vector(Vector const& source);
//     Vector& operator=(Vector const& source);

    ~Vector();

  private:
    double xDirection;
    double yDirection;
    double zDirection;

  public:
    double x() const;
    double y() const;
    double z() const; /**< Undefined in 2D. */

    /**
      Compute vector length.
     @note 3D space safe.
      */
    double length() const;


    void setX(double coordinate);
    void setY(double coordinate);
    void setZ(double coordinate);

    void set(double xCoord, double yCoord, double zCoord = 0);
    void set(Point const& first, Point const& second);

    void rotateAroundX(double degrees);
    void rotateAroundY(double degrees);
    void rotateAroundZ(double degrees);

    void normalize();

    /**
      Compute standard dot product of two vectors
      in 3D space.
     @param[in] vector Second vector for the dot product.
     @return Dot product result.
     */
    double dotProduct(Vector const& vector);

    /**
      Compute 'perp dot' product.
     @remarks
       Used primarily in MinimalCycleBasis.
       2D only!
     @note
       Explained at http://mathworld.wolfram.com/PerpDotProduct.html

     @param[in] vector Second vector for the dot product.
     @return Resulting product.
     */
    double perpDotProduct(Vector const& vector);

    /**
      Compute cross product of the two vectors.
     @note
       Explained at http://mathworld.wolfram.com/CrossProduct.html .

     @param[in] vector Second vector for the cross product.
     @return Resulting product.
      */
    Vector crossProduct(Vector const& vector);

    /**
      Compute angle between two vectors.
     @remarks
       The resulting angle is always between 0 and PI.
       If one of the vectors has zero length, returns nan.
     @note
       Formula is explained at http://mathworld.wolfram.com/DotProduct.html (9).

     @param[in] second Vector wich angle we want to determine from current vector.
     @return Resulting angle in RADIANS.
     */
    double angleTo(Vector const& second);

    /**
      Compute angle between the Vector and X axis (Vector(1,0)).
     @remarks
       The result is in [0, 2PI) interval. Works correctly only in 2D.
     @note
       Method is explained at http://en.wikipedia.org/wiki/Atan2 .

     @return Resulting angle in RADIANS.
     */
    double angleToXAxis();

    bool   operator==(Vector const& second);
    bool   operator!=(Vector const& second);
    Vector operator*(double constant);
    Vector operator/(double constant);
    Vector operator+(Vector const& vector);

    /**
      Returns vector as a string for debugging purposes.
     @return Format is like: Vector(x, y, z).
     */
    std::string toString();
};
#endif