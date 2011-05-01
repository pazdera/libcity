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

