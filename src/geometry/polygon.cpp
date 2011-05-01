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
#include "units.h"
#include "point.h"
#include "vector.h"
#include "linesegment.h"
#include "ray.h"
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

Polygon::Polygon(Polygon const& source)
{
  initialize();

  for (std::vector<Point*>::iterator vertex = source.vertices->begin();
       vertex != source.vertices->end();
       vertex++)
  {
    addVertex(**vertex);
  }
}

Polygon& Polygon::operator=(Polygon const& source)
{
  freeVertices();
  initialize();

  for (std::vector<Point*>::iterator vertex = source.vertices->begin();
       vertex != source.vertices->end();
       vertex++)
  {
    addVertex(**vertex);
  }

  return *this;
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

void Polygon::clear()
{
  vertices->clear();
}

void Polygon::addVertex(Point const& vertex)
{
  vertices->push_back(new Point(vertex));

  // FIXME: check if the vertex is in a plane with other vertices!
}

void Polygon::updateVertex(unsigned int number, Point const& vertex)
{
  assert(number < vertices->size());
  *vertices->at(number) = vertex;
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
  assert(number < numberOfVertices());
  return *vertices->at(number);
}

LineSegment Polygon::edge(unsigned int number) const
{
  assert(numberOfVertices() >= 2);
  assert(number < (numberOfVertices()));

  return LineSegment(*vertices->at(number), *vertices->at((number + 1) % numberOfVertices()));
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

    areaStep = currentVertex->x() * nextVertex->y() - nextVertex->x() * currentVertex->y();
    area += areaStep;

    x += (currentVertex->x() + nextVertex->x()) * areaStep;
    y += (currentVertex->y() + nextVertex->y()) * areaStep;
  }

  Point centroid(x/(6*(area/2)), y/(6*(area/2)));
  return centroid;
}

bool Polygon::encloses2D(Point const& point) const
{
  unsigned int currentVertexPosition = 0,
               count = numberOfVertices();
  Point *currentVertex = 0,
        *nextVertex = 0;
  LineSegment currentLine;

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


Vector Polygon::normal()
{
  assert(numberOfVertices() >= 3);

  Vector first(*vertices->at(1), *vertices->at(0)),
         second;

  double angle;
  int current, next, verticesCount = numberOfVertices();
  for (int i = 1; i < verticesCount; i++)
  {
    current = i;
    next = (i + 1) % verticesCount;
    second.set(*vertices->at(current), *vertices->at(next));
    angle = std::abs(first.angleTo(second));

    /* Edges are not parallel */
    if (std::abs(angle - 0) > libcity::EPSILON &&
        std::abs(angle - libcity::PI) > libcity::EPSILON)
    {

      Vector normalVector = first.crossProduct(second);
      normalVector.normalize();
      return normalVector;
    }
  }

  assert("HERE should be exception" == 0);
}

Vector Polygon::edgeNormal(unsigned int edgeNumber)
{
  unsigned int verticesNumber = numberOfVertices();
  assert(edgeNumber < verticesNumber);

  int first  = edgeNumber;
  int second = (edgeNumber + 1) % verticesNumber;

  Vector direction(*(vertices->at(first)), *(vertices->at(second))),
         normalVector;

  normalVector = direction.crossProduct(normal());
  normalVector.normalize();

  Point edgeCenter((vertices->at(first)->x() + vertices->at(second)->x())/2,
                   (vertices->at(first)->y() + vertices->at(second)->y())/2,
                   (vertices->at(first)->z() + vertices->at(second)->z())/2);

  Ray testRay(edgeCenter, normalVector);

  Point intersection;
  int intersections = 0, vertexHits = 0;
  for (unsigned int i = 0; i < (verticesNumber); i++)
  {
    LineSegment currentEdge = edge(i);
    if (i != edgeNumber &&
        testRay.intersection2D(currentEdge, &intersection) == Ray::INTERSECTING)
    {
      if (intersection == currentEdge.begining() ||
          intersection == currentEdge.end())
      {
        vertexHits++;
      }
      intersections++;
    }
  }
  assert((vertexHits % 2) == 0);
  intersections -= vertexHits/2;


  return (intersections % 2) ? normalVector : normalVector*(-1);
}

bool Polygon::isSubAreaOf(Polygon const& biggerPolygon)
{
  for (unsigned int i = 0; i < numberOfVertices(); i++)
  {
    if (!biggerPolygon.encloses2D(*(*vertices)[i]))
    {
      return false;
    }
  }

  return true;
}


std::list<Polygon*> Polygon::split(LineSegment const& splitLine)
{
  std::list<Point> vertexList;
  std::list<Point> intersections;

  LineSegment currentEdge;
  LineSegment::Intersection result;
  Point intersection;

  /* for each edge */
  for (unsigned int i = 0; i < numberOfVertices(); i++)
  {
    currentEdge = edge(i);

    vertexList.push_back(vertex(i));

    result = splitLine.intersection2D(currentEdge, &intersection);
    if (result == LineSegment::INTERSECTING)
    {
      if (intersection != currentEdge.begining() &&
          intersection != currentEdge.end())
      {
        vertexList.push_back(intersection);
      }

      intersections.push_back(intersection);
//       /* Insert-sort into intersections */
//       std::list<Point>::iterator appropriatePosition = intersections.begin();
//       while (appropriatePosition != intersections.end() && *appropriatePosition < intersection)
//       {
//         appropriatePosition++;
//       }
//       intersections.insert(appropriatePosition, intersection);
    }
  }
  intersections.sort();

  std::list<Polygon*> stack;
  std::list<Polygon*> output;
  Polygon* top;

  stack.push_back(new Polygon);
  for (std::list<Point>::iterator vertexIterator = vertexList.begin();
       vertexIterator != vertexList.end();
       vertexIterator++)
  {
    top = stack.back();

    top->addVertex(*vertexIterator);

    if (isVertexIntersection(*vertexIterator, intersections))
    {
      if (top->numberOfVertices() > 0 && areVerticesInPair(*vertexIterator, top->vertex(0), intersections))
      {
        output.push_back(top);
        stack.pop_back();
        top = stack.back();
        top->addVertex(*vertexIterator);
      }
      else
      {
        stack.push_back(new Polygon);
        top = stack.back();
        top->addVertex(*vertexIterator);
      }
    }
  }

  return output;
}

bool Polygon::isVertexIntersection(Point vertex, std::list<Point> intersections)
{
  for (std::list<Point>::iterator vertexIterator = intersections.begin();
       vertexIterator != intersections.end();
       vertexIterator++)
  {
    if (*vertexIterator == vertex)
    {
      return true;
    }
  }

  return false;
}

bool Polygon::areVerticesInPair(Point first, Point second, std::list<Point> intersections)
{
  int i = 0;
  std::list<Point>::iterator vertexIterator;
  for (vertexIterator =intersections.begin();
       vertexIterator != intersections.end();
       vertexIterator++, i++)
  {
    if (*vertexIterator == first)
    {
      if (i % 2)
      {
        vertexIterator--;
      }
      else
      {
        vertexIterator++;
      }
      break;
    }
  }

  assert(vertexIterator != intersections.end());
  return *vertexIterator == second;
}


void Polygon::rotate(double xDegrees, double yDegrees, double zDegrees)
{
  Point center = centroid();

  Vector centroidToVertex;
  for (unsigned int i = 0; i < numberOfVertices(); i++)
  {
    centroidToVertex = vertex(i) - center;
    centroidToVertex.rotate(xDegrees, yDegrees, zDegrees);
    updateVertex(i, center + centroidToVertex);
  }
}

std::string Polygon::toString()
{
  std::string output = "Polygon(";

  for (unsigned int i = 0; i < numberOfVertices(); i++)
  {
    output += (*vertices)[i]->toString() + ", ";
  }
  return output + ").";
}