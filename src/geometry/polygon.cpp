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
#include "line.h"
#include "../debug.h"

#include <cmath>

void Polygon::initialize()
{
  vertices = new std::vector<Point*>;
}

Polygon::Polygon()
{
  initialize();
}

Polygon::Polygon(Point const& one, Point const& two, Point const& three)
{
  initialize();
  addVertex(one);
  addVertex(two);
  addVertex(three);
}

Polygon::Polygon(Point const& one, Point const& two, Point const& three, Point const& four)
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

unsigned int Polygon::numberOfVertices() const
{
  return vertices->size();
}

void Polygon::addVertex(Point const& vertex)
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

Point Polygon::vertex(unsigned int number) const
{
  return *vertices->at(number);
}

double Polygon::area() const
{
  return std::abs(signedArea());
}

double Polygon::signedArea() const
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

Point Polygon::centroid() const
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

bool Polygon::hasPoint2D(Point const& point) const
{
  unsigned int currentVertexPosition = 0,
               count = numberOfVertices();
  Point *currentVertex = 0,
        *nextVertex = 0;
  Line currentLine;

  bool isInside = false;

  for (currentVertexPosition = 0; currentVertexPosition < count; currentVertexPosition++)
  {
    currentVertex = vertices->at(currentVertexPosition);
    nextVertex    = vertices->at((currentVertexPosition + 1) % count);

    /* The algorithm is unreilable at the edges so
     * we check them separately to make sure. */
    currentLine.setBegining(*currentVertex);
    currentLine.setEnd(*nextVertex);
    if (currentLine.hasPoint2D(point))
    {
      return true;
    }

    if (((currentVertex->y() > point.y()) != (nextVertex->y() > point.y())) &&
        (point.x() < (nextVertex->x() - currentVertex->x()) / (nextVertex->y() - currentVertex->y())
                     * (point.y() - currentVertex->y()) + currentVertex->x())
       )
    {
       isInside = !isInside;
    }
  }

  return isInside;

}