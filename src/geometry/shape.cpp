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
{}

Shape::Shape(Shape const& source)
{}

Shape& Shape::operator=(Shape const& source)
{}

Shape::~Shape()
{
  freeMemory();
}

void Shape::freeMemory()
{}

Polygon Shape::base() const
{}

Vector Shape::height() const
{}

void Shape::setBase(Polygon const& polygon)
{}

void Shape::setHeight(double const& number)
{}

