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

    bool operator==(Point second);
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

#endif