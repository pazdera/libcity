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

#include <string>

class Vector;

class Point
{
  public:
    Point(); /**< [0,0,0] */
    Point(double const& x, double const& y); /**< 2D */
    Point(double const& x, double const& y, double const& z); /**< 3D */
    Point(Point const& source);

    ~Point();

    std::string toString();

  private:
    double xPosition;
    double yPosition;
    double zPosition;

  public:
    double x() const;
    double y() const;
    double z() const; /**< Undefined in 2D. */

    void set(double const& xCoord, double const& yCoord, double const& zCoord = 0);
    void setX(double const& coordinate);
    void setY(double const& coordinate);
    void setZ(double const& coordinate);

    bool operator==(Point const& second);
    bool operator<(Point const& second);
    bool operator>(Point const& second);

    Point& operator+=(Vector const& difference);
    Point  operator+(Vector const& difference);
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

inline void Point::setX(double const& coordinate)
{
  xPosition = coordinate;
}

inline void Point::setY(double const& coordinate)
{
  yPosition = coordinate;
}

inline void Point::setZ(double const& coordinate)
{
  zPosition = coordinate;
}

#endif