/**
 * This code is part of libcity library.
 *
 * @file geometry/ray.h
 * @date 15.04.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @brief Representation of a ray
 *
 * Also basic geometric operation with line are implemented
 * here.
 */

#ifndef _RAY_H_
#define _RAY_H_

#include <string>

class Point;
class Vector;

class Ray
{
  public:
    enum Intersection
    {
      INTERSECTING = 0,
      NONINTERSECTING,
      PARALLEL,
      IDENTICAL
    };

    Ray();
    Ray(Point const& point, Vector const& vector);

    Ray(Ray const& source);
    Ray& operator=(Ray const& source);

    ~Ray();

    void set(Point const& point, Vector const& vector);
    void setOrigin(Point const& point);
    void setDirection(Vector const& vector);

    Point  origin() const;
    Vector direction() const;

    Intersection intersection2D(Ray const& another, Point* intersection) const;

    std::string toString();

    //bool operator==(Ray const& second) const;

  private:
    Point* rayOrigin;
    Vector* rayDirection;

    void initialize();
    void freeMemory();
};

#endif
