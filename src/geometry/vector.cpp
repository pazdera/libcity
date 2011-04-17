/**
 * This code is part of libcity library.
 *
 * @file geometry/vector.cpp
 * @date 05.03.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @see geometry/vector.h
 *
 */

#include "vector.h"
#include "units.h"

#include "point.h"
#include "../debug.h"

#include <sstream>
#include <cmath>

Vector::Vector()
  : xDirection(0.0), yDirection(0.0), zDirection(0.0)
{}

Vector::Vector(double x)
  : xDirection(x), yDirection(0.0), zDirection(0.0)
{}

Vector::Vector(double x, double y)
  : xDirection(x), yDirection(y), zDirection(0.0)
{}

Vector::Vector(double x, double y, double z)
  : xDirection(x), yDirection(y), zDirection(z)
{}

Vector::~Vector()
{}

double Vector::x() const
{
  return xDirection;
}

double Vector::y() const
{
  return yDirection;
}

double Vector::z() const
{
  return zDirection;
}

void Vector::setX(double coordinate)
{
  xDirection = coordinate;
}

void Vector::setY(double coordinate)
{
  yDirection = coordinate;
}

void Vector::setZ(double coordinate)
{
  zDirection = coordinate;
}

void Vector::rotateAroundX(double degrees)
{
  double radians = degrees * (libcity::PI/180.0);
  double newX, newY, newZ;

  newX = 1.0*xDirection;
  newY = yDirection*cos(radians) - zDirection*sin(radians);
  newZ = yDirection*sin(radians) + zDirection*cos(radians);

  xDirection = newX;
  yDirection = newY;
  zDirection = newZ;
}

void Vector::rotateAroundY(double degrees)
{
  double radians = degrees * (libcity::PI/180.0);
  double newX, newY, newZ;

  newX = zDirection*sin(radians) + xDirection*cos(radians);
  newY = 1.0*yDirection;
  newZ = zDirection*cos(radians) - xDirection*sin(radians);

  xDirection = newX;
  yDirection = newY;
  zDirection = newZ;
}

void Vector::rotateAroundZ(double degrees)
{
  double radians = degrees * (libcity::PI/180.0);
  double newX = 0.0,
         newY = 0.0,
         newZ = 0.0;

  newX = xDirection*cos(radians) - yDirection*sin(radians);
  newY = xDirection*sin(radians) + yDirection*cos(radians);
  newZ = 1.0*zDirection;

  xDirection = newX;
  yDirection = newY;
  zDirection = newZ;
}

void Vector::normalize()
{
  double vectorLength = length();

  xDirection /= vectorLength;
  yDirection /= vectorLength;
  zDirection /= vectorLength;
}

double Vector::length() const
{
  return sqrt(xDirection*xDirection + yDirection*yDirection + zDirection*zDirection);
}

void Vector::set(double xCoord, double yCoord, double zCoord)
{
  xDirection = xCoord;
  yDirection = yCoord;
  zDirection = zCoord;
}

void Vector::set(Point const& first, Point const& second)
{
  xDirection = second.x() - first.x();
  yDirection = second.y() - first.y();
  zDirection = second.z() - first.z();
}

std::string Vector::toString()
{
  std::stringstream convertor;
  convertor << "Vector(" << xDirection << ", " << yDirection << ", " << zDirection << ")";
  return convertor.str();
}

double Vector::dotProduct(Vector const& vector)
{
  return x()*vector.x() + y()*vector.y() + z()*vector.z();
}

double Vector::perpDotProduct(Vector const& vector)
{
  return x()*vector.y() - vector.x()*y();
}

Vector Vector::crossProduct(Vector const& vector)
{
  double resultX = y()*vector.z() - z()*vector.y(),
         resultY = z()*vector.x() - x()*vector.z(),
         resultZ = x()*vector.y() - y()*vector.x();

  return Vector(resultX, resultY, resultZ);
}

double Vector::angleTo(Vector const& vector)
{
  Vector first(*this), second(vector);
  first.normalize();
  second.normalize();

  return std::acos(first.dotProduct(second)/(first.length()*second.length()));
}

double Vector::angleToXAxis()
{
  /* This produces results in the range (−PI, PI], which can be
  mapped to [0, 2PI) by adding 2PI to negative values. */
  double angle = atan2(y(), x()); 

  if (angle < 0)
  {
    angle += 2*libcity::PI;
  }

  return angle;
}

bool   Vector::operator==(Vector const& second)
{
  return (xDirection - second.x()) < libcity::EPSILON &&
         (yDirection - second.y()) < libcity::EPSILON &&
         (zDirection - second.z()) < libcity::EPSILON;
}

Vector Vector::operator*(double constant)
{
  return Vector(constant*xDirection, constant*yDirection, constant*zDirection);
}

Vector Vector::operator/(double constant)
{
  return Vector(xDirection/constant, yDirection/constant, zDirection/constant);
}

Vector Vector::operator+(Vector const& vector)
{
  return Vector(xDirection + vector.x(), yDirection + vector.y(), zDirection + vector.z());
}

Vector::Vector(Point const& first, Point const& second)
{
  set(first, second);
}