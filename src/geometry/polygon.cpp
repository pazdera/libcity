/**
 * This code is part of libcity library.
 *
 * @file geometry/polygon.cpp
 * @date 19.03.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @see geometry/polygon.h
 *
 */

#include "polygon.h"
#include "point.h"

#include <cmath>

void Polygon::initialize()
{
  vertices = new std::vector<Point*>;
}

Polygon::Polygon()
{
  initialize();
}

Polygon::Polygon(Point one, Point two, Point three)
{
  initialize();
  addVertex(one);
  addVertex(two);
  addVertex(three);
}

Polygon::Polygon(Point one, Point two, Point three, Point four)
{
  initialize();
  addVertex(one);
  addVertex(two);
  addVertex(three);
  addVertex(four);
}

Polygon::~Polygon()
{
  freeVertices();
}

void Polygon::freeVertices()
{
  while (!vertices->empty())
  {
    delete vertices->back();
    vertices->pop_back();
  }

  delete vertices;
}

unsigned int Polygon::numberOfVertices()
{
  return vertices->size();
}

void Polygon::addVertex(Point vertex)
{
  vertices->push_back(new Point(vertex));

  // FIXME: check if the vertex is in a plane with other vertices!
}

void Polygon::removeVertex(unsigned int number)
{
  if (number >= vertices->size())
  {
    // FIXME throw out of range exception
  }

  Point *removedVertex = vertices->at(number);
  vertices->erase(vertices->begin() + number);
  delete removedVertex;
}

Point Polygon::vertex(unsigned int number)
{
  return *vertices->at(number);
}

double Polygon::area()
{
  return std::abs(signedArea());
}

double Polygon::signedArea()
{
  double area = 0;

  unsigned int currentVertexPosition = 0,
               count = numberOfVertices();
  Point *currentVertex = 0,
        *nextVertex = 0;

  for (currentVertexPosition = 0; currentVertexPosition < count; currentVertexPosition++)
  {
    currentVertex = vertices->at(currentVertexPosition);
    nextVertex    = vertices->at((currentVertexPosition + 1) % count);

    area += currentVertex->x() * nextVertex->y() - currentVertex->y() * nextVertex->x();
  }

  return area/2;
}

Point Polygon::centroid()
{
  double area     = 0,
         areaStep = 0;
  double x = 0,
         y = 0;

  unsigned int currentVertexPosition = 0,
               count = numberOfVertices();
  Point *currentVertex = 0,
        *nextVertex = 0;

  for (currentVertexPosition = 0; currentVertexPosition < count; currentVertexPosition++)
  {
    currentVertex = vertices->at(currentVertexPosition);
    nextVertex    = vertices->at((currentVertexPosition + 1) % count);

    areaStep = currentVertex->x() * nextVertex->y() - currentVertex->y() * nextVertex->x();
    area += areaStep;

    x += (currentVertex->x() * nextVertex->x()) / areaStep;
    y += (currentVertex->y() * nextVertex->y()) / areaStep;
  }

  return Point(x/(3*area), (y/3*area));
}