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
  /* To avoid zero length edges. */
  if (numberOfVertices() > 0)
  {
    double distanceFromLast = Vector(vertex, *vertices->back()).length();

    if (distanceFromLast <= libcity::COORDINATES_EPSILON)
    {
      return;
    }
  }

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

Vector Polygon::normal() const
{
  assert(numberOfVertices() >= 3);

  Vector first(*vertices->at(1), *vertices->at(0)),
         second;

  first.normalize();

  int current, next, verticesCount = numberOfVertices();
  for (int i = 1; i < verticesCount; i++)
  {
    current = i;
    next = (i + 1) % verticesCount;
    second.set(*vertices->at(current), *vertices->at(next));
    second.normalize();

    /* Edges are not parallel */
    if (first != second && first != second*(-1))
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

void Polygon::scale(double factor)
{
  assert(factor > 0);
  Point center = centroid();

  Vector centroidToVertex;
  for (unsigned int i = 0; i < numberOfVertices(); i++)
  {
    centroidToVertex = vertex(i) - center;
    updateVertex(i, center + centroidToVertex*factor);
  }
}

void Polygon::substract(double distance)
{
  int previous, current, next;
  int verticesCount = numberOfVertices();
  Line first, second;
  Vector firstNormal, secondNormal;
  Line::Intersection result;
  Point newVertex;
  Polygon oldArea(*this);

  for(int i = 0; i < verticesCount; i++)
  {
    previous = (i-1) < 0 ? verticesCount-1 : i-1;
    current = i;
    next = (i + 1) % verticesCount;

    firstNormal = oldArea.edgeNormal(previous);
    firstNormal.normalize();
    first.setBegining(oldArea.vertex(previous) + firstNormal*distance);
    first.setEnd(oldArea.vertex(current) + firstNormal*distance);

    secondNormal = oldArea.edgeNormal(current);
    secondNormal.normalize();
    second.setBegining(oldArea.vertex(current) + secondNormal*distance);
    second.setEnd(oldArea.vertex(next) + secondNormal*distance);

    result = first.intersection2D(second, &newVertex);
    if (result == Line::PARALLEL)
    {
      newVertex = oldArea.vertex(current) + firstNormal*distance;
    }

    updateVertex(current, newVertex);
  }
}

void Polygon::substractEdge(int edgeNumber, double distance)
{
  assert(numberOfVertices() >= 3);

  int previous, current1, current2, next;
  int verticesCount = numberOfVertices();

  previous = (edgeNumber-1) < 0 ? verticesCount-1 : edgeNumber-1;
  current1 = edgeNumber;
  current2 = (edgeNumber + 1) % verticesCount;
  next     = (edgeNumber + 2) % verticesCount;

  Vector normal = edgeNormal(edgeNumber);
  normal.normalize();
  Line first(vertex(previous), vertex(current1)),
       second(vertex(next), vertex(current2)),
       center(vertex(current1) + normal*distance, vertex(current2) + normal*distance);

  Point newVertex1, newVertex2;
  Line::Intersection result;

  result = first.intersection2D(center, &newVertex1);
  if (result == Line::PARALLEL)
  {
    newVertex1 = vertex(current1) + normal*distance;
  }
  updateVertex(current1, newVertex1);

  result = second.intersection2D(center, &newVertex2);
  if (result == Line::PARALLEL)
  {
    newVertex2 = vertex(current2) + normal*distance;
  }
  updateVertex(current2, newVertex2);

}

bool Polygon::isNonSelfIntersecting()
{
//   LineSegment first, second;
//   Point intersection;
//   for (unsigned int i = 0; i < numberOfVertices()-1; i++)
//   {
//     first = edge(i);
//     for (unsigned int j = i+1; j < numberOfVertices(); j++)
//     {
//       second = edge(j);
//       if (first.intersection2D(second, &intersection) == LineSegment::INTERSECTING)
//       {
//         if (intersection != first.begining() && intersection != first.end())
//         {
//           return false;
//         }
//       }
//     }
//   }
  std::vector<Point> points;
  std::vector<int> sequence;

  return triangulation(&points, &sequence);

}

std::string Polygon::toString() const
{
  std::string output = "Polygon(";

  for (unsigned int i = 0; i < numberOfVertices(); i++)
  {
    output += (*vertices)[i]->toString() + ", ";
  }
  return output + ").";
}



   /*
     isInsideTriangle decides if a point P is Inside of the triangle
     defined by A, B, C.
   */
bool Polygon::isInsideTriangle(double Ax, double Ay,
                      double Bx, double By,
                      double Cx, double Cy,
                      double Px, double Py)

{
  double ax, ay, bx, by, cx, cy, apx, apy, bpx, bpy, cpx, cpy;
  double cCROSSap, bCROSScp, aCROSSbp;

  ax = Cx - Bx;  ay = Cy - By;
  bx = Ax - Cx;  by = Ay - Cy;
  cx = Bx - Ax;  cy = By - Ay;
  apx= Px - Ax;  apy= Py - Ay;
  bpx= Px - Bx;  bpy= Py - By;
  cpx= Px - Cx;  cpy= Py - Cy;

  aCROSSbp = ax*bpy - ay*bpx;
  cCROSSap = cx*apy - cy*apx;
  bCROSScp = bx*cpy - by*cpx;

  return ((aCROSSbp >= 0.0) && (bCROSScp >= 0.0) && (cCROSSap >= 0.0));
}

bool Polygon::snip(int u,int v,int w,int n,int *V)
{
  int p;
  double Ax, Ay, Bx, By, Cx, Cy, Px, Py;

  Ax = (*vertices)[V[u]]->x();
  Ay = (*vertices)[V[u]]->y();

  Bx = (*vertices)[V[v]]->x();
  By = (*vertices)[V[v]]->y();

  Cx = (*vertices)[V[w]]->x();
  Cy = (*vertices)[V[w]]->y();

  if ( libcity::EPSILON > (((Bx-Ax)*(Cy-Ay)) - ((By-Ay)*(Cx-Ax))) )
  {
    return false;
  }

  for (p=0;p<n;p++)
  {
    if( (p == u) || (p == v) || (p == w) ) continue;
    Px = (*vertices)[V[p]]->x();
    Py = (*vertices)[V[p]]->y();
    if (isInsideTriangle(Ax,Ay,Bx,By,Cx,Cy,Px,Py)) return false;
  }

  return true;
}

std::vector<Point> Polygon::triangulate()
{
  std::vector<Point> points;
  std::vector<int> sequence;

  triangulation(&points, &sequence);

  return points;
}

std::vector<int> Polygon::getSurfaceIndexes()
{
  std::vector<Point> points;
  std::vector<int> sequence;

  triangulation(&points, &sequence);

  return sequence;
}

bool Polygon::triangulation(std::vector<Point> *points, std::vector<int> *sequence)
{
  /* allocate and initialize list of Vertices in polygon */
  assert(numberOfVertices() >= 3);

  int n = vertices->size();

  int *V = new int[n];

  /* we want a counter-clockwise polygon in V */

  if ( 0.0 < signedArea() )
    for (int v=0; v<n; v++) V[v] = v;
  else
    for(int v=0; v<n; v++) V[v] = (n-1)-v;

  int nv = n;

  /*  remove nv-2 Vertices, creating 1 triangle every time */
  int count = 2*nv;   /* error detection */

  for(int m=0, v=nv-1; nv>2; )
  {
    /* if we loop, it is probably a non-simple polygon */
    if (0 >= (count--))
    {
      //** Triangulate: ERROR - probable bad polygon!
      return false;
    }

    /* three consecutive vertices in current polygon, <u,v,w> */
    int u = v  ; if (nv <= u) u = 0;     /* previous */
    v = u+1; if (nv <= v) v = 0;     /* new v    */
    int w = v+1; if (nv <= w) w = 0;     /* next     */

    if ( snip(u,v,w,nv,V) )
    {
      int a,b,c,s,t;

      /* true names of the vertices */
      a = V[u]; b = V[v]; c = V[w];

      /* output Triangle */
      points->push_back( *((*vertices)[a]) );
      points->push_back( *((*vertices)[b]) );
      points->push_back( *((*vertices)[c]) );

      sequence->push_back(a);
      sequence->push_back(b);
      sequence->push_back(c);

      m++;

      /* remove v from remaining polygon */
      for(s=v,t=v+1;t<nv;s++,t++) V[s] = V[t]; nv--;

      /* resest error detection counter */
      count = 2*nv;
    }
  }

  delete V;

  return true;
}