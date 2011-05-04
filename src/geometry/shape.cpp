/**
 * This code is part of libcity library.
 *
 * @file geometry/shape.cpp
 * @date 01.05.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @see geometry/shape.h
 *
 */

#include "shape.h"
#include "polygon.h"
#include "units.h"
#include "point.h"
#include "vector.h"
#include "linesegment.h"
#include "../debug.h"

#include <cmath>
#include <string>
#include <sstream>

Shape::Shape()
{
  initialize();
}

Shape::Shape(Polygon const& base, double height)
{}

void Shape::initialize()
{
  shapeBase   = new Polygon();
  shapeHeight = 0;
}

Shape::Shape(Shape const& source)
{
  initialize();

  *shapeBase = *(source.shapeBase);
  shapeHeight = source.shapeHeight;
}

Shape& Shape::operator=(Shape const& source)
{
  *shapeBase = *(source.shapeBase);
  shapeHeight = source.shapeHeight;

  return (*this);
}

Shape::~Shape()
{
  freeMemory();
}

void Shape::freeMemory()
{
  delete shapeBase;
}

Polygon Shape::base() const
{
  return *shapeBase;
}

Polygon Shape::top() const
{
  Polygon upperBase;
  for (unsigned int i = 0; i < shapeBase->numberOfVertices(); i++)
  {
    upperBase.addVertex(shapeBase->vertex(i) + Vector(0,0,1)*shapeHeight);
  }

  return upperBase;
}

double Shape::height() const
{
  return shapeHeight;
}

void Shape::setBase(Polygon const& polygon)
{
  *shapeBase = polygon;
}

void Shape::setHeight(double const& number)
{
  shapeHeight = number;
}

bool Shape::encloses(Point const& point)
{
  assert(shapeBase->numberOfVertices() > 0);

  double lowerZBound  = shapeBase->vertex(0).z(),
         higherZBound = lowerZBound + shapeHeight;

  return shapeBase->encloses2D(point) && point.z() >= lowerZBound && point.z() <= higherZBound;
}

bool Shape::encloses(Shape const& shape)
{
  Polygon otherBase = shape.base();
  for (unsigned int i = 0; i < otherBase.numberOfVertices(); i++)
  {
    if (!encloses(otherBase.vertex(i)) ||
        !encloses(otherBase.vertex(i) + Vector(0,0,1)*shape.height()))
    {
      return false;
    }
  }

  return true;
}

bool Shape::encloses(Polygon const& polygon)
{
  for (unsigned int i = 0; i < polygon.numberOfVertices(); i++)
  {
    if (!encloses(polygon.vertex(i)))
    {
      return false;
    }
  }

  return true;
}

std::string Shape::toString()
{
  std::stringstream output;
  output << "Shape(" << shapeBase->toString();
  output << ", height = " << shapeHeight << ")";

  return output.str();
}