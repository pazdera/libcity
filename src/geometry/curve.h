/**
 * This code is part of libcity library.
 *
 * @file geometry/curve.h
 * @date 19.02.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @brief Representation of curve
 *
 */

class Point;

class Curve
{
  public:
    Curve();
    ~Curve();

  private:
    Point *begining;
    Point *end;
};