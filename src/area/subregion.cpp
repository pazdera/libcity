/**
 * This code is part of libcity library.
 *
 * @file area/subregion.cpp
 * @date 28.04.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @see subregion.h
 *
 */

#include "subregion.h"

#include <sstream>
#include <string>

#include "../debug.h"
#include "../geometry/units.h"
#include "../geometry/point.h"
#include "../geometry/polygon.h"
#include "../geometry/vector.h"
#include "../geometry/linesegment.h"

SubRegion::SubRegion()
{
  initialize();
}

SubRegion::SubRegion(Polygon const& polygon)
{
  initialize();
  polygonGraph = constructPolygonGraph(polygon);
}

SubRegion::SubRegion(Edge* edge)
{
  initialize();
  polygonGraph = copyPolygonGraph(edge);
}

SubRegion::SubRegion(SubRegion const& source)
{
  initialize();

  polygonGraph = copyPolygonGraph(source.polygonGraph);
}

void SubRegion::initialize()
{
  polygonGraph = 0;
}

SubRegion& SubRegion::operator=(SubRegion const& source)
{
  freeMemory();
  polygonGraph = copyPolygonGraph(source.polygonGraph);

  return *this;
}

SubRegion::~SubRegion()
{
  freeMemory();
}

void SubRegion::freeMemory()
{
  Edge* first = polygonGraph;
  while(polygonGraph->next != first)
  {
    polygonGraph = polygonGraph->next;
    delete polygonGraph->previous;
  }
}


SubRegion::Edge* SubRegion::getLongestEdgeWithRoadAccess()
{
  assert(polygonGraph != 0);

  Edge* current = polygonGraph;
  Edge* longest = 0;

  do
  {
    if (longest == 0 && current->hasRoadAccess)
    {
      longest = current;
    }

    if (current->hasRoadAccess &&
       ((current->begining - current->next->begining).length() >
       (longest->begining - longest->next->begining).length()))
    {
      longest = current;
    }
    current = current->next;
  }
  while(current != polygonGraph);

  return longest;
}

SubRegion::Edge* SubRegion::getLongestEdgeWithoutRoadAccess()
{
  Edge* current = polygonGraph;
  Edge* longest = 0;

  do
  {
    if (longest == 0 && !current->hasRoadAccess)
    {
      longest = current;
    }

    if (!current->hasRoadAccess &&
       ((current->begining - current->next->begining).length() >
       (longest->begining - longest->next->begining).length()))
    {
      longest = current;
    }
    current = current->next;
  }
  while(current != polygonGraph);

  return longest;
}

bool SubRegion::hasRoadAccess()
{
  Edge* current = polygonGraph;

  do
  {
    if (current->hasRoadAccess)
    {
      return true;
    }
    current = current->next;
  }
  while(current != polygonGraph);

  return false;
}

SubRegion::Edge* SubRegion::constructPolygonGraph(Polygon const& polygon)
{
  assert(polygon.numberOfVertices() >= 3);

  Edge* current = new Edge;
  Edge* first = current;
  Edge* next;
  Edge* previous = 0;
  for (unsigned int i = 0; i < polygon.numberOfVertices(); i++)
  {
    current->begining = polygon.vertex(i);
    current->hasRoadAccess = false;

    next = new Edge;
    previous = current;
    current->next = next;
    next->previous = current;

    current = next;
  }

  /* Connect the end to the begining */
  current = next->previous;  // one step back
  delete next;               // discard the prepared node
  current->next = first;     // connect to cycle
  first->previous = current; // and back

  return first;
}

SubRegion::Edge* SubRegion::copyPolygonGraph(Edge* source)
{
  Edge* sourceCurrent = source;

  Edge* current = new Edge;
  Edge* first = current;
  Edge* next;
  Edge* previous = 0;

  do
  {
    current->begining = sourceCurrent->begining;
    current->hasRoadAccess = sourceCurrent->hasRoadAccess; // All block edges have road access
    current->s = sourceCurrent->s;

    next = new Edge;
    previous = current;
    current->next = next;
    next->previous = current;
    current = next;

    sourceCurrent = sourceCurrent->next;
  }
  while(sourceCurrent != source);

  /* Connect the end to the begining */
  current = next->previous;  // one step back
  delete next;               // discard the prepared node
  current->next = first;     // connect to cycle
  first->previous = current; // and back

  return first;
}

SubRegion::Edge* SubRegion::getFirstEdge()
{
  return polygonGraph;
}

SubRegion::Edge* SubRegion::insert(Edge* after, Point const& begining)
{
  if (polygonGraph == 0)
  {
    return insertFirst(begining);
  }

  assert(after != 0);

  Edge* newEdge = new Edge;
  newEdge->begining = begining;
  newEdge->hasRoadAccess = false;
  newEdge->s = 0;

  Edge* next = after->next;
  after->next = newEdge;
  newEdge->previous = after;
  newEdge->next = next;
  next->previous = newEdge;

  return newEdge;
}

SubRegion::Edge* SubRegion::insertFirst(Point const& begining)
{
  polygonGraph = new Edge;
  polygonGraph->begining = begining;
  polygonGraph->hasRoadAccess = false;
  polygonGraph->s = 0;

  polygonGraph->previous = polygonGraph;
  polygonGraph->next = polygonGraph;

  return polygonGraph;
}

void SubRegion::bridge(Edge* first, Edge* second)
{
  Edge* otherFirst;
  Edge* otherSecond;

  debug("BRIDGING GRAPH:");
  debug("  First  road access = " << first->hasRoadAccess);
  debug("  Second road access = " << second->hasRoadAccess);
  otherFirst = insert(first, first->begining);
  otherFirst->hasRoadAccess = first->hasRoadAccess;

  otherSecond = insert(second, second->begining);
  otherSecond->hasRoadAccess = second->hasRoadAccess;

  first->next  = otherSecond;
  otherSecond->previous = first;

  second->next = otherFirst;
  otherFirst->previous = second;

  debug(" after:");
  debug("  First  road access = " << first->hasRoadAccess);
  debug("  Second road access = " << second->hasRoadAccess);

  first->hasRoadAccess  = false;
  second->hasRoadAccess = false;
//   SubRegion::Edge* current = first;
//   do
//   {
//     current = current->next;
//   } while (current != first);
// 
//   current = second;
//   do
//   {
//     current = current->next;
//   } while (current != second);
}

Polygon SubRegion::toPolygon()
{
  Edge* current = polygonGraph;
  Polygon polygon;

  do
  {
    polygon.addVertex(current->begining);
    current = current->next;
  }
  while(current != polygonGraph);

  return polygon;
}

std::string SubRegion::toString()
{
  Edge* current = polygonGraph;
  std::stringstream output;

  output << "SubRegion( \n";
  do
  {
    output << "  Edge(\n";
    output << "    point      = " << current->begining.toString() << "\n";
    output << "    roadAccess = " << current->hasRoadAccess << "\n";
    output << "    s          = " << current->s << "),\n";
    current = current->next;
  }
  while(current != polygonGraph);
  output << ")\n";

  return output.str();
}
