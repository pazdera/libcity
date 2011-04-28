/**
 * This code is part of libcity library.
 *
 * @file area/region.cpp
 * @date 28.04.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @see region.h
 *
 */

#include "region.h"

#include "../debug.h"
#include "../geometry/units.h"
#include "../geometry/point.h"
#include "../geometry/polygon.h"
#include "../geometry/vector.h"
#include "../geometry/linesegment.h"

Region::Region()
{
  initialize();
}

Region::Region(Region const& source)
{
  initialize();

  //*constraints = *(source.constraints);
  polygonGraph = copyPolygonGraph(source.polygonGraph);
}

void Region::initialize()
{
  polygonGraph = 0;
  //constraints = new Polygon();
}

Region& Region::operator=(Region const& source)
{
  //*constraints = *(source.constraints);
  polygonGraph = copyPolygonGraph(source.polygonGraph);

  return *this;
}

Region::~Region()
{
  freeMemory();
}

void Region::freeMemory()
{
  //delete constraints;
  Edge* first = polygonGraph;
  while(polygonGraph->next != first)
  {
    polygonGraph = polygonGraph->next;
    delete polygonGraph->previous;
  }
}


Region::Edge* Region::getLongestEdgeWithRoadAccess()
{
  Edge* current = polygonGraph;
  Edge* longest = 0;

  while(current->next != polygonGraph)
  {
    if (((current->begining - current->next->begining).length() >
         (longest->begining - longest->next->begining).length() && !current->hasRoadAccess) ||
        (longest == 0 && !current->hasRoadAccess))
    {
      longest = current;
    }
    current = current->next;
  }

  return longest;
}

Region::Edge* Region::getLongestEdgeWithoutRoadAccess()
{
  Edge* current = polygonGraph;
  Edge* longest = 0;

  while(current->next != polygonGraph)
  {
    if (((current->begining - current->next->begining).length() >
         (longest->begining - longest->next->begining).length() && !current->hasRoadAccess) ||
        (longest == 0 && !current->hasRoadAccess))
    {
      longest = current;
    }
    current = current->next;
  }

  return longest;
}

bool Region::hasRoadAccess()
{
  Edge* current = polygonGraph;
  while(current->next != polygonGraph)
  {
    if (current->hasRoadAccess)
    {
      return true;
    }
    current = current->next;
  }

  return false;
}

Region::Edge* Region::constructPolygonGraph(Polygon const& polygon)
{
  assert(polygon.numberOfVertices() >= 3);

  Edge* current = new Edge;
  Edge* first = current;
  Edge* previous = 0;
  for (unsigned int i = 0; i < polygon.numberOfVertices(); i++)
  {
    current->begining = polygon.vertex(i);
    current->hasRoadAccess = false;
    current->next = new Edge;
    current->previous = previous;
    previous = current;
    current = current->next;
  }

  /* Connect the end to the begining */
  current = current->previous;
  delete current->next;
  current->next = first;
  first->previous = current;

  return current;
}

Region::Edge* Region::copyPolygonGraph(Edge* source)
{
  Edge* sourceCurrent = source;

  Edge* current = new Edge;
  Edge* first = current;
  Edge* previous = 0;
  while(sourceCurrent->next != source)
  {
    current->begining = sourceCurrent->begining;
    current->hasRoadAccess = sourceCurrent->hasRoadAccess; // All block edges have road access
    current->next = new Edge;
    current->previous = previous;
    previous = current;
    current = current->next;

    sourceCurrent = sourceCurrent->next;
  }

  /* Connect the end to the begining */
  current = current->previous;
  delete current->next;
  current->next = first;
  first->previous = current;

  return first;
}

Polygon Region::constructPolygon(Edge* graph)
{
  Edge* current = polygonGraph;
  Polygon polygon;
  while(current->next != polygonGraph)
  {
    polygon.addVertex(current->begining);
    current = current->next;
  }

  return polygon;
}

Region::Edge* Region::getPolygonGraph()
{
  return polygonGraph;
}

Region::Edge* Region::getPolygonGraphCopy()
{
  return copyPolygonGraph(polygonGraph);
}

Region::Edge* Region::insertToPolygonGraph(Edge* after, Point const& begining)
{
  assert(after != 0);

  Edge* next = after->next;
  after->next = new Edge;
  after->next->previous = after;
  after->next->next = next;
  next->previous = after->next;

  return after->next;
}

void Region::bridge(Edge* first, Edge* second)
{
  Edge* otherFirst;
  Edge* otherSecond;

  otherFirst = insertToPolygonGraph(first, first->begining);
  otherFirst->hasRoadAccess = false;

  otherSecond = insertToPolygonGraph(second->previous, second->begining);
  otherSecond->hasRoadAccess = false;

  first->next  = otherSecond;
  otherSecond->previous = first;

  second->next = otherFirst;
  otherFirst->previous = second;
}