/**
 * This code is part of libcity library.
 *
 * @file minimalcyclebasis.cpp
 * @date 31.03.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @see minimalcyclebasis.h
 *
 */

#include "minimalcyclebasis.h"
#include "intersection.h"
#include "../geometry/point.h"
#include "../geometry/polygon.h"
#include "../geometry/vector.h"
#include "../debug.h"

MinimalCycleBasis::MinimalCycleBasis(std::list<Intersection*>* inputIntersections)
{
  initialize();

  /* Add all nodes into adjacency list. */
  for (std::list<Intersection*>::iterator insertedIntersectionIterator = inputIntersections->begin();
       insertedIntersectionIterator != inputIntersections->end();
       insertedIntersectionIterator++)
  {
    addVertex(*insertedIntersectionIterator);
  }
}

void MinimalCycleBasis::initialize()
{
  vertices = new std::list<Intersection*>;
  adjacentNodes = new std::map< Intersection*, std::vector<Intersection*> >;
  cycleEdges = new std::set< std::pair<Intersection*, Intersection*> >;
  cycles = new std::list<Polygon>;
}

MinimalCycleBasis::~MinimalCycleBasis()
{
  freeMemory();
}

void MinimalCycleBasis::freeMemory()
{
  delete vertices;
  delete adjacentNodes;
  delete cycleEdges;
  delete cycles;
}

MinimalCycleBasis::MinimalCycleBasis(MinimalCycleBasis const& source)
{
  initialize();

  *vertices      = *(source.vertices);
  *adjacentNodes = *(source.adjacentNodes);
  *cycleEdges    = *(source.cycleEdges);
  *cycles        = *(source.cycles);
}

MinimalCycleBasis& MinimalCycleBasis::operator=(MinimalCycleBasis const& source)
{
  freeMemory();
  initialize();

  *vertices      = *(source.vertices);
  *adjacentNodes = *(source.adjacentNodes);
  *cycleEdges    = *(source.cycleEdges);
  *cycles        = *(source.cycles);

  return *this;
}

Intersection* MinimalCycleBasis::getClockwiseMost(Intersection *previous, Intersection* current)
{
  std::vector<Intersection*> adjacentNodes = adjacent(current);

  Vector vCurrent = previous ? Vector(current->position(), previous->position()) : Vector(0, -1);
  Vector vNext;
  Intersection* next = 0;
  double vCurrentIsConvex = false;

  Intersection* adjacent = 0;
  Vector vAdjacent(0,0,0);
  for (std::vector<Intersection*>::iterator adjacentNode = adjacentNodes.begin();
       adjacentNode != adjacentNodes.end();
       adjacentNode++)
  {
    adjacent = *adjacentNode;

    if (adjacent == previous)
    {
      continue;
    }

    vAdjacent.set(adjacent->position(), current->position());

    if (!next)
    {
        next = adjacent;
        vNext = vAdjacent;
        vCurrentIsConvex = (vNext.dotProduct(vCurrent) <= 0);
        continue;
    }

    if (vCurrentIsConvex)
    {
      if (vCurrent.dotProduct(vAdjacent) < 0 || vNext.dotProduct(vAdjacent) < 0)
      {
          next = adjacent;
          vNext = vAdjacent;
          vCurrentIsConvex = vNext.dotProduct(vCurrent) <= 0;
      }
    }
    else
    {
      if (vCurrent.dotProduct(vAdjacent) < 0 && vNext.dotProduct(vAdjacent) < 0)
      {
          next = adjacent;
          vNext = vAdjacent;
          vCurrentIsConvex = vNext.dotProduct(vCurrent) <= 0;
      }
    }
  }

  return next;
}

void MinimalCycleBasis::extractIsolatedVertex(Intersection* vertex)
{
  removeVertex(vertex);
}

void MinimalCycleBasis::extractFilament(Intersection* v0, Intersection* v1)
{
  if (isCycleEdge(v0,v1))
  {
    if (numberOfAdjacentNodes(v0) >= 3)
    {
      removeEdge(v0,v1);
      v0 = v1;
      if (numberOfAdjacentNodes(v0) == 1)
      {
        v1 = firstAdjacentNode(v0);
      }
    }

    while (numberOfAdjacentNodes(v0) == 1)
    {
      v1 = firstAdjacentNode(v0);
      if (isCycleEdge(v0,v1))
      {
        removeEdge(v0,v1);
        removeVertex(v0);
        v0 = v1;
      }
      else
      {
        break;
      }
    }
    if (numberOfAdjacentNodes(v0) == 0)
    {
      removeVertex(v0);
    }
  }
  else
  {
    if (numberOfAdjacentNodes(v0) >= 3)
    {
      removeEdge(v0,v1);
      v0 = v1;
      if (numberOfAdjacentNodes(v0) == 1)
      {
        v1 = firstAdjacentNode(v0);
      }
    }

    while (numberOfAdjacentNodes(v0) == 1)
    {
      v1 = firstAdjacentNode(v0);
      removeEdge(v0,v1);
      removeVertex(v0);
      v0 = v1;
    }

    if (numberOfAdjacentNodes(v0) == 0)
    {
      removeEdge(v0,v1);
      removeVertex(v0);
    }
  }
}

void MinimalCycleBasis::extractMinimalCycle(Intersection* current, Intersection* next)
{
  std::set<Intersection*> visited;
  std::list<Intersection*> sequence;

  sequence.push_back(current);
  next = getClockwiseMost(0, current);

  Intersection* previousVertex = current;
  Intersection* currentVertex  = next;
  Intersection* nextVertex  = 0;
  while ((currentVertex != 0) &&
         (currentVertex != current) &&
         (visited.find(currentVertex) == visited.end()))
  {
    sequence.push_back(currentVertex);
    visited.insert(currentVertex);
    nextVertex = getCounterclockwiseMost(previousVertex, currentVertex);
    previousVertex = currentVertex;
    currentVertex = nextVertex;
  }

  if (currentVertex == 0)
  {
    // Filament found, not necessarily rooted at v0.
    extractFilament(previousVertex,firstAdjacentNode(previousVertex));
  }
  else if (currentVertex == current)
  {
    // Minimal cycle found.
    Polygon minimalCycle;

    for (std::list<Intersection*>::iterator nodeInCycle = sequence.begin();
          nodeInCycle != sequence.end();
          nodeInCycle++)
    {
      minimalCycle.addVertex((*nodeInCycle)->position());

      std::list<Intersection*>::iterator nextNodeInCycle = nodeInCycle;
      nextNodeInCycle++;
      if (nextNodeInCycle == sequence.end())
      {
        nextNodeInCycle = sequence.begin();
      }
      markCycleEdge(*nodeInCycle, *nextNodeInCycle);
    }

    cycles->push_back(minimalCycle);

    removeEdge(current, next);

    if (numberOfAdjacentNodes(current) == 1)
    {
      // Remove the filament rooted at v0.
      extractFilament(current,firstAdjacentNode(current));
    }
    if (numberOfAdjacentNodes(next) == 1)
    {
      // Remove the filament rooted at v1.
      extractFilament(next,firstAdjacentNode(next));
    }
  }
  else   // vcurr was visited earlier
  {
    // A cycle has been found, but is not guaranteed to be a minimal
    // cycle. This implies v0 is part of a filament. Locate the
    // starting point for the filament by traversing from v0 away
    // from the initial v1.
    while (numberOfAdjacentNodes(current) == 2)
    {
      std::vector<Intersection*> adjacentNodes = adjacent(current);
      if (adjacentNodes.front() != next)
      {
          next = current;
          current = adjacentNodes.front();
      }
      else
      {
          next = current;
          current = adjacentNodes.back();
      }
    }
    extractFilament(current,next);
  }
}

std::list<Polygon> MinimalCycleBasis::getMinimalCycles()
{
  std::vector<Intersection*> adjacentNodes;
  Intersection* current;
  Intersection* next;

  while (!empty())
  {
    current = first();
    debug(current->position().toString());

    adjacentNodes = adjacent(current);

    if (adjacentNodes.size() == 0)
    /* Isolated, no cycle possible. */
    {
      extractIsolatedVertex(current);
    }
    else if (adjacentNodes.size() == 1)
    /* Remove filaments */
    {
      next = adjacentNodes[0];
      extractFilament(current, next);
    }
    else
    /* Extract cycles. */
    {
      next = adjacentNodes[0];
      extractMinimalCycle(current, next);
    }
  }

  return *cycles;
}

Intersection* MinimalCycleBasis::getCounterclockwiseMost(Intersection *previous, Intersection* current)
{
  std::vector<Intersection*> adjacentNodes = adjacent(current);

  Vector vCurrent = previous ? Vector(current->position(), previous->position()) : Vector(0, -1);
  Vector vNext;
  Intersection* next = 0;
  double vCurrentIsConvex = false;

  Intersection* adjacent = 0;
  Vector vAdjacent(0,0,0);
  for (std::vector<Intersection*>::iterator adjacentNode = adjacentNodes.begin();
       adjacentNode != adjacentNodes.end();
       adjacentNode++)
  {
    adjacent = *adjacentNode;

    if (adjacent == previous)
    {
      continue;
    }

    vAdjacent.set(adjacent->position(), current->position());

    if (!next)
    {
        next = adjacent;
        vNext = vAdjacent;
        vCurrentIsConvex = (vNext.dotProduct(vCurrent) <= 0);
        continue;
    }

    if (vCurrentIsConvex)
    {
      if (vCurrent.dotProduct(vAdjacent) > 0 && vNext.dotProduct(vAdjacent) > 0)
      {
          next = adjacent;
          vNext = vAdjacent;
          vCurrentIsConvex = vNext.dotProduct(vCurrent) <= 0;
      }
    }
    else
    {
      if (vCurrent.dotProduct(vAdjacent) > 0 || vNext.dotProduct(vAdjacent) > 0)
      {
          next = adjacent;
          vNext = vAdjacent;
          vCurrentIsConvex = vNext.dotProduct(vCurrent) <= 0;
      }
    }
  }

  return next;
}

int MinimalCycleBasis::numberOfAdjacentNodes(Intersection* node)
{
  return (*adjacentNodes)[node].size();
}

void MinimalCycleBasis::addVertex(Intersection* node)
{
  /* Insert adjacent intersections. */
  adjacentNodes->insert(std::pair< Intersection*, std::vector<Intersection*> >(node, node->adjacentIntersections()));

  std::list<Intersection*>::iterator sequenceIterator;
  Intersection* existing;

  /* Determine where to sort current node. */
  for (sequenceIterator  = vertices->begin();
       sequenceIterator != vertices->end();
       sequenceIterator++)
  {
    existing = *sequenceIterator;

    if (node->position().x() < existing->position().x())
    /* X coordinate of newly added intersection is smaller. Insert it before. */
    {
      break;
    }
    else if (node->position().x() == existing->position().x())
    /* X coordinates are the same. Y will be used to decide. */
    {
      if (node->position().y() < existing->position().y())
      /* Y of newly added intersection is smaller. Insert it before. */
      {
        break;
      }
      else
      /* Y are greater or equal */
      {
        sequenceIterator++;
        break;
      }
    }
    else
    /* Ckeck further points. */
    {
      continue;
    }
  }

  /* Insert into list. */
  vertices->insert(sequenceIterator, node);
}

void MinimalCycleBasis::removeVertex(Intersection* node)
{
  vertices->remove(node);

  for(std::vector<Intersection*>::iterator adjacentNode = (*adjacentNodes)[node].begin();
      adjacentNode != (*adjacentNodes)[node].end();
      adjacentNode++)
  {
    removeEdge(node, *adjacentNode);
  }

  adjacentNodes->erase(node);
}

void MinimalCycleBasis::removeEdge(Intersection* begining, Intersection* end)
{
  /* Remove second point from adjacency list of first point. */
  for (std::vector<Intersection*>::iterator adjacentNode = (*adjacentNodes)[begining].begin();
       adjacentNode != (*adjacentNodes)[begining].end();
       adjacentNode++)
  {
    if (*adjacentNode == end)
    {
      (*adjacentNodes)[begining].erase(adjacentNode);
      break;
    }
  }

  /* And vice versa. */
  for (std::vector<Intersection*>::iterator adjacentNode = (*adjacentNodes)[end].begin();
       adjacentNode != (*adjacentNodes)[end].end();
       adjacentNode++)
  {
    if (*adjacentNode == begining)
    {
      (*adjacentNodes)[end].erase(adjacentNode);
      break;
    }
  }

  /* If edge was marked as cycle edge, remove the mark as well. */
  cycleEdges->erase(std::make_pair(begining, end));
  cycleEdges->erase(std::make_pair(end, begining));
}

Intersection* MinimalCycleBasis::first()
{
  return vertices->front();
}

std::vector<Intersection*> MinimalCycleBasis::adjacent(Intersection* node)
{
  if (adjacentNodes->find(node) == adjacentNodes->end())
  {
    std::vector<Intersection*> empty;
    // FIXME exception not in graph
    return empty;
  }

  return (*adjacentNodes)[node];
}

bool MinimalCycleBasis::empty()
{
  return vertices->empty();
}

Intersection* MinimalCycleBasis::firstAdjacentNode(Intersection* node)
{
  // FIXME throw exception when empty
  assert(numberOfAdjacentNodes(node) > 0);

  return adjacent(node).front();
}

bool MinimalCycleBasis::isCycleEdge(Intersection* begining, Intersection* end)
{
  return cycleEdges->find(std::make_pair(begining, end)) != cycleEdges->end() ||
         cycleEdges->find(std::make_pair(end, begining)) != cycleEdges->end();
}

void MinimalCycleBasis::markCycleEdge(Intersection* begining, Intersection* end)
{
  cycleEdges->insert(std::make_pair(begining, end));
}