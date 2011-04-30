/**
 * This code is part of libcity library.
 *
 * @file areaextractor.cpp
 * @date 31.03.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @see areaextractor.h
 *
 */

#include "areaextractor.h"
#include "intersection.h"
#include "../area/zone.h"
#include "../area/block.h"
#include "../streetgraph/streetgraph.h"
#include "../geometry/units.h"
#include "../geometry/point.h"
#include "../geometry/line.h"
#include "../geometry/polygon.h"
#include "../geometry/vector.h"
#include "../debug.h"

#include <cmath>

AreaExtractor::AreaExtractor()
{
  initialize();
}

void AreaExtractor::initialize()
{
  vertices = new std::list<Intersection*>;
  adjacentNodes = new std::map< Intersection*, std::vector<Intersection*> >;
  cycleEdges = new std::set< std::pair<Intersection*, Intersection*> >;
  cycles = new std::list<Polygon>;

  reset();
}

void AreaExtractor::reset()
{
  vertices->clear();
  adjacentNodes->clear();
  cycleEdges->clear();
  cycles->clear();
  substractRoadWidthFromAreas = false;
}

AreaExtractor::~AreaExtractor()
{
  freeMemory();
}

void AreaExtractor::freeMemory()
{
  delete vertices;
  delete adjacentNodes;
  delete cycleEdges;
  delete cycles;
}

AreaExtractor::AreaExtractor(AreaExtractor const& source)
{
  initialize();

  *vertices      = *(source.vertices);
  *adjacentNodes = *(source.adjacentNodes);
  *cycleEdges    = *(source.cycleEdges);
  *cycles        = *(source.cycles);
}

AreaExtractor& AreaExtractor::operator=(AreaExtractor const& source)
{
  reset();

  *vertices      = *(source.vertices);
  *adjacentNodes = *(source.adjacentNodes);
  *cycleEdges    = *(source.cycleEdges);
  *cycles        = *(source.cycles);

  return *this;
}

void AreaExtractor::copyVertices(StreetGraph* map, Zone* zone)
{
  reset();

  /* Add all nodes into adjacency list. */
  StreetGraph::Intersections inputIntersections = map->getIntersections();
  for (std::list<Intersection*>::iterator insertedIntersectionIterator = inputIntersections.begin();
       insertedIntersectionIterator != inputIntersections.end();
       insertedIntersectionIterator++)
  {
    addVertex(*insertedIntersectionIterator, zone);
  }
}


void AreaExtractor::setRoadWidth(Road::Types type, double width)
{
  roadWidths[type] = width;
}

void AreaExtractor::setRoadWidths(std::map<Road::Types, double> widths)
{
  roadWidths = widths;
}

std::list<Zone*> AreaExtractor::extractZones(StreetGraph* fromMap, Zone* zoneConstraints)
{
  reset();
  map = fromMap;
  copyVertices(map, zoneConstraints);
  substractRoadWidthFromAreas = false;

  getMinimalCycles();

  std::list<Zone*> zones;
  for (std::list<Polygon>::iterator foundZone = cycles->begin();
       foundZone != cycles->end();
       foundZone++)
  {
    Zone* newZone = new Zone(map);
    newZone->setAreaConstraints(*foundZone);
    zones.push_back(newZone);
  }

  return zones;
}

std::list<Block*> AreaExtractor::extractBlocks(StreetGraph* fromMap, Zone* zoneConstraints)
{
  reset();
  map = fromMap;
  copyVertices(map, zoneConstraints);
  substractRoadWidthFromAreas = true;
  std::list<Block*> blocks;

  getMinimalCycles();

  for (std::list<Polygon>::iterator foundZone = cycles->begin();
       foundZone != cycles->end();
       foundZone++)
  {
    Block* newBlock = new Block(zoneConstraints);
    newBlock->setAreaConstraints(*foundZone);
    blocks.push_back(newBlock);
  }
  return blocks;
}

std::vector<double> AreaExtractor::getSubstractDistances(std::vector<Intersection*> intersections)
{
  /* Get width of all edges */
  std::vector<double> edgeWidth;
  int current, next;
  Road* road;
  for (unsigned int i = 0; i < intersections.size(); i++)
  {
    current = i;
    next = (i+1) % intersections.size();

    road  = map->getRoadBetweenIntersections(intersections[current], intersections[next]);
    assert(roadWidths.find(road->type()) != roadWidths.end());

    edgeWidth.push_back(roadWidths[road->type()]);
  }

  return edgeWidth;
}

void AreaExtractor::minimalizeCycle(Polygon* minimalCycle, std::vector<double>* distances)
{
  double isMinimal = false;
  while (!isMinimal)
  {
    int previous, current, next, verticesCount = minimalCycle->numberOfVertices();
    isMinimal = true;
    for (int i = 0; i < verticesCount; i++)
    {
      previous = (i-1) < 0 ? verticesCount-1 : i-1;
      current = i;
      next = (i + 1) % verticesCount;

      if (previous == next)
      {
        break;
      }

      Vector first(minimalCycle->vertex(current), minimalCycle->vertex(previous)),
             second(minimalCycle->vertex(current), minimalCycle->vertex(next));

      if (first.isParallelWith(second))
      {
        minimalCycle->removeVertex(current);
        distances->erase(distances->begin() + current);
        isMinimal = false;
        break;
      }
    }
  }
}

void AreaExtractor::substractRoadWidths(Polygon* minimalCycle, std::vector<double> const& distances)
{
  assert(minimalCycle->numberOfVertices() == distances.size());

  Polygon oldArea(*minimalCycle);
  int current, next, previous;
  int vertices = minimalCycle->numberOfVertices();
  Vector previousNormal, currentNormal;
  Line previousEdge, currentEdge;
  Point newVertex;

  for(int i = 0; i < vertices; i++)
  {
    previous = (i-1) < 0 ? vertices-1 : i-1;
    current = i;
    next = (i + 1) % vertices;

    previousNormal = oldArea.edgeNormal(previous);
    currentNormal  = oldArea.edgeNormal(current);
    previousNormal.normalize();
    currentNormal.normalize();

    previousEdge.setBegining(oldArea.vertex(current) + previousNormal*distances[previous]);
    previousEdge.setEnd(oldArea.vertex(previous) + previousNormal*distances[previous]);

    currentEdge.setBegining(oldArea.vertex(current) + currentNormal*distances[current]);
    currentEdge.setEnd(oldArea.vertex(next) + currentNormal*distances[current]);

    Line::Intersection result;
    result = currentEdge.intersection2D(previousEdge, &newVertex);
    if (result == Line::PARALLEL)
    {
      double distance = distances[previous];
      if (distance < distances[current])
      {
        distance = distances[current];
      }
      newVertex = oldArea.vertex(current) + currentNormal*distance;
    }

    minimalCycle->updateVertex(current, newVertex);
  }
}

void AreaExtractor::getMinimalCycles()
{
  std::vector<Intersection*> adjacentNodes;
  Intersection* current;
  Intersection* next;

  while (!empty())
  {
    current = first();

    adjacentNodes = adjacent(current);

    if (adjacentNodes.size() == 0)
    /* Isolated, no cycle possible. */
    {
      debug("AreaExtractor::getMinimalCycles(): Extracting isolated vertex.");
      extractIsolatedVertex(current);
    }
    else if (adjacentNodes.size() == 1)
    /* Remove filaments */
    {
      debug("AreaExtractor::getMinimalCycles(): Extracting filament.");
      next = adjacentNodes[0];
      extractFilament(current, next);
    }
    else
    /* Extract cycles. */
    {
      debug("AreaExtractor::getMinimalCycles(): Extracting minimal cycle.");
      next = adjacentNodes[0];
      extractMinimalCycle(current, next);
    }
  }
}

void AreaExtractor::extractIsolatedVertex(Intersection* vertex)
{
  removeVertex(vertex);
}

void AreaExtractor::extractFilament(Intersection* v0, Intersection* v1)
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

void AreaExtractor::extractMinimalCycle(Intersection* current, Intersection* next)
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
    debug("AreaExtractor::extractMinimalCycle(): Next point in sequence is " << currentVertex->position().toString());
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
    std::vector<Intersection*> correspondingIntersections;

    for (std::list<Intersection*>::iterator nodeInCycle = sequence.begin();
          nodeInCycle != sequence.end();
          nodeInCycle++)
    {
      minimalCycle.addVertex((*nodeInCycle)->position());
      correspondingIntersections.push_back(*nodeInCycle);

      std::list<Intersection*>::iterator nextNodeInCycle = nodeInCycle;
      nextNodeInCycle++;
      if (nextNodeInCycle == sequence.end())
      /* So we can mark the last edge */
      {
        nextNodeInCycle = sequence.begin();
      }
      markCycleEdge(*nodeInCycle, *nextNodeInCycle);
    }

    debug("AreaExtractor::extractMinimalCycle(): Storing minimal cycle.");
    if (substractRoadWidthFromAreas)
    {
      std::vector<double> distances = getSubstractDistances(correspondingIntersections);
      Polygon boundaries(minimalCycle);
      minimalizeCycle(&minimalCycle, &distances);
      substractRoadWidths(&minimalCycle, distances);

      // Discard wrong blocks
      if (minimalCycle.isSubAreaOf(boundaries))
      {
        cycles->push_back(minimalCycle);
      }
        //cycles->push_back(minimalCycle);
    }
    else
    {
      cycles->push_back(minimalCycle);
    }

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

Intersection* AreaExtractor::getClockwiseMost(Intersection *previous, Intersection* current)
{
  std::vector<Intersection*> adjacentNodes = adjacent(current);

  Vector vCurrent = previous != 0 ? Vector(current->position(), previous->position()) : Vector(0, -1);
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
        vCurrentIsConvex = (vNext.perpDotProduct(vCurrent) <= -libcity::EPSILON);
        continue;
    }

    if (vCurrentIsConvex)
    {
      if (vCurrent.perpDotProduct(vAdjacent) < 0 || vNext.perpDotProduct(vAdjacent) < 0)
      {
          next = adjacent;
          vNext = vAdjacent;
          vCurrentIsConvex = vNext.perpDotProduct(vCurrent) <= -libcity::EPSILON;
      }
    }
    else
    {
      if (vCurrent.perpDotProduct(vAdjacent) < 0 && vNext.perpDotProduct(vAdjacent) < 0)
      {
          next = adjacent;
          vNext = vAdjacent;
          vCurrentIsConvex = vNext.perpDotProduct(vCurrent) <= -libcity::EPSILON;
      }
    }
  }

  return next;
}

Intersection* AreaExtractor::getCounterclockwiseMost(Intersection *previous, Intersection* current)
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
        vCurrentIsConvex = (vNext.perpDotProduct(vCurrent) <= -libcity::EPSILON);
        continue;
    }

    if (vCurrentIsConvex)
    {
      if (vCurrent.perpDotProduct(vAdjacent) > 0 && vNext.perpDotProduct(vAdjacent) > 0)
      {
          next = adjacent;
          vNext = vAdjacent;
          vCurrentIsConvex = vNext.perpDotProduct(vCurrent) <= -libcity::EPSILON;
      }
    }
    else
    {
      if (vCurrent.perpDotProduct(vAdjacent) > 0 || vNext.perpDotProduct(vAdjacent) > 0)
      {
          next = adjacent;
          vNext = vAdjacent;
          vCurrentIsConvex = vNext.perpDotProduct(vCurrent) <= -libcity::EPSILON;
      }
    }
  }

  return next;
}

int AreaExtractor::numberOfAdjacentNodes(Intersection* node)
{
  return (*adjacentNodes)[node].size();
}

void AreaExtractor::addVertex(Intersection* node, Zone* zone)
{
  std::vector<Intersection*> adjacent = node->adjacentIntersections();

  if (zone != 0)
  {
    if (!zone->isIntersectionInside(node))
    {
      return;
    }

    std::vector<Intersection*> adjacentNodesInZone;
    for (unsigned int i = 0; i < adjacent.size(); i++)
    {
      if (zone->isIntersectionInside(adjacent[i]))
      {
        adjacentNodesInZone.push_back(adjacent[i]);
      }
    }
    adjacent.clear();
    adjacent.assign(adjacentNodesInZone.begin(), adjacentNodesInZone.end());
  }


  /* Insert adjacent intersections. */
  adjacentNodes->insert(std::pair< Intersection*, std::vector<Intersection*> >(node, adjacent));

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

void AreaExtractor::removeVertex(Intersection* node)
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

void AreaExtractor::removeEdge(Intersection* begining, Intersection* end)
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

Intersection* AreaExtractor::first()
{
  return vertices->front();
}

std::vector<Intersection*> AreaExtractor::adjacent(Intersection* node)
{
  if (adjacentNodes->find(node) == adjacentNodes->end())
  {
    std::vector<Intersection*> empty;
    // FIXME exception not in graph
    return empty;
  }

  return (*adjacentNodes)[node];
}

bool AreaExtractor::empty()
{
  return vertices->empty();
}

Intersection* AreaExtractor::firstAdjacentNode(Intersection* node)
{
  // FIXME throw exception when empty
  assert(numberOfAdjacentNodes(node) > 0);

  return adjacent(node).front();
}

bool AreaExtractor::isCycleEdge(Intersection* begining, Intersection* end)
{
  return cycleEdges->find(std::make_pair(begining, end)) != cycleEdges->end() ||
         cycleEdges->find(std::make_pair(end, begining)) != cycleEdges->end();
}

void AreaExtractor::markCycleEdge(Intersection* begining, Intersection* end)
{
  cycleEdges->insert(std::make_pair(begining, end));
}

void AreaExtractor::dumpAdjacencyLists()
{
  for (std::map< Intersection*, std::vector<Intersection*> >::iterator nodeIterator = adjacentNodes->begin();
       nodeIterator != adjacentNodes->end();
       nodeIterator++)
  {
    debug((*nodeIterator).first->position().toString() << " Has this adjacent nodes :");
    for (std::vector<Intersection*>::iterator adjacentNodeIterator = (*nodeIterator).second.begin();
         adjacentNodeIterator != (*nodeIterator).second.end();
         adjacentNodeIterator++)
    {
      debug("  " << (*adjacentNodeIterator)->position().toString());
    }
  }
}

void AreaExtractor::dumpAdjacenciesFromVertices()
{
  for (std::list<Intersection*>::iterator nodeIterator = vertices->begin();
       nodeIterator != vertices->end();
       nodeIterator++)
  {
    debug((*nodeIterator)->position().toString() << " Has this adjacent nodes :");
    std::vector<Intersection*> adjacent = (*nodeIterator)->adjacentIntersections();
    for (std::vector<Intersection*>::iterator adjacentNodeIterator = adjacent.begin();
         adjacentNodeIterator != adjacent.end();
         adjacentNodeIterator++)
    {
      debug("  " << (*adjacentNodeIterator)->position().toString());
    }
  }
}