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

void Vector::rotate(double xDegrees, double yDegrees, double zDegrees)
{
  rotateAroundX(xDegrees);
  rotateAroundY(yDegrees);
  rotateAroundZ(zDegrees);
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

double Vector::squaredLength() const
{
  return xDirection*xDirection + yDirection*yDirection + zDirection*zDirection;
}

void Vector::set(double xCoord, double yCoord, double zCoord)
{
  xDirection = xCoord;
  yDirection = yCoord;
  zDirection = zCoord;
}

void Vector::set(Point const& from, Point const& to)
{
  xDirection = to.x() - from.x();
  yDirection = to.y() - from.y();
  zDirection = to.z() - from.z();
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

bool Vector::isParallelWith(Vector const& second)
{
  double angle = angleTo(second);
  return std::abs(angle - 0) <= libcity::EPSILON || std::abs(angle - libcity::PI) <= libcity::EPSILON;
}

Vector Vector::crossProduct(Vector const& vector)
{
  /* Vectors are parallel, thats undefined. */
  assert(!isParallelWith(vector));

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

  double product = first.dotProduct(second);

  // Check the borders with an EPSILON
  if (std::abs(product - 1) <= libcity::EPSILON)
  {
    product = 1;
  }

  if (std::abs(product + 1) <= libcity::EPSILON)
  {
    product = -1;
  }

  return std::acos(product);
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
  return std::abs(xDirection - second.x()) < libcity::COORDINATES_EPSILON &&
         std::abs(yDirection - second.y()) < libcity::COORDINATES_EPSILON &&
         std::abs(zDirection - second.z()) < libcity::COORDINATES_EPSILON;
}

bool   Vector::operator!=(Vector const& second)
{
  return !(*this == second);
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

Vector::Vector(Point const& from, Point const& to)
{
  set(from, to);
}

Point Vector::toPoint()
{
  return Point(xDirection, yDirection, zDirection);
}
