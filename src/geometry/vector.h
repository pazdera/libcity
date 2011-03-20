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
#endif