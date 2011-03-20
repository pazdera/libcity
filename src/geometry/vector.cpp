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
  double radians = degrees * (libcity::PI/180);
  double newX, newY, newZ;

  newX = xDirection;
  newY = yDirection*cos(radians) - zDirection*sin(radians);
  newZ = yDirection*sin(radians) + zDirection*cos(radians);

  xDirection = newX;
  yDirection = newY;
  zDirection = newZ;
}

void Vector::rotateAroundY(double degrees)
{
  double radians = degrees * (libcity::PI/180);
  double newX, newY, newZ;

  newX = zDirection*sin(radians) + xDirection*cos(radians);
  newY = yDirection;
  newZ = zDirection*cos(radians) - xDirection*sin(radians);

  xDirection = newX;
  yDirection = newY;
  zDirection = newZ;
}

void Vector::rotateAroundZ(double degrees)
{
  double radians = degrees * (libcity::PI/180);
  double newX, newY, newZ;

  newX = xDirection*cos(radians) - yDirection*sin(radians);
  newY = xDirection*sin(radians) + yDirection*cos(radians);
  newZ = zDirection;

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

double Vector::length()
{
  return sqrt(xDirection*xDirection + yDirection*yDirection + zDirection*zDirection);
}

void Vector::set(double xCoord, double yCoord, double zCoord)
{
  xDirection = xCoord;
  yDirection = yCoord;
  zDirection = zCoord;
}

bool   Vector::operator==(Vector second)
{
  return xDirection == second.x() &&
         yDirection == second.y() &&
         zDirection == second.z();
}

Vector Vector::operator*(double constant)
{
  return Vector(constant*xDirection, constant*yDirection, constant*zDirection);
}

Vector Vector::operator/(double constant)
{
  return Vector(xDirection/constant, yDirection/constant, zDirection/constant);
}

Vector Vector::operator+(Vector vector)
{
  return Vector(xDirection + vector.x(), yDirection + vector.y(), zDirection + vector.z());
}

