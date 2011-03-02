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

#endif