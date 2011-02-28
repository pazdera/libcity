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

class Point
{
  public:
    Point();
    Point(int x, int y);
    Point(int x, int y, int z);
    ~Point();

  private:
    int xPosition;
    int yPosition;
    int zPosition;

  public:
    int x() const;
    int y() const;
    int z() const;

    void setX(int coordinate);
    void setY(int coordinate);
    void setZ(int coordinate);
};