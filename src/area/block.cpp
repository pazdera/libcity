/**
 * This code is part of libcity library.
 *
 * @file area/block.cpp
 * @date 25.04.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @see block.h
 *
 */

#include "block.h"


#include <cmath>

#include "../debug.h"
#include "../random.h"
#include "../geometry/units.h"
#include "../geometry/point.h"
#include "../geometry/polygon.h"
#include "../geometry/vector.h"
#include "../geometry/linesegment.h"
#include "zone.h"
#include "lot.h"

Block::Block()
{
  initialize();
}

Block::Block(Zone* parentZone)
{
  initialize();
  setParent(parentZone);
}

Block::Block(Zone* parentZone, Polygon const& border)
{
  initialize();
  setParent(parentZone);
  setAreaConstraints(border);
}

Block::Block(Block const& source)
  : Area(source)
{
  initialize();
}

void Block::initialize()
{
  lots.clear();
}

Block& Block::operator=(Block const& source)
{
  Area::operator=(source);

  return *this;
}

Block::~Block()
{
  freeMemory();
}

void Block::freeMemory()
{
  lots.clear();
}

void Block::createLots()
{
  const double MAX_LOT_WIDTH = 100;
  const double MAX_LOT_DEPTH = 100;
  const double LOT_DEVIANCE  = 0;

  Area* region;
  std::vector<Area*> regionQueue;
  std::vector<Area*> newRegions;
  std::vector<Area*> outputRegions;
  Area::Edge* longestEdge;
  LineSegment edgeLine;
  double splitSize;
  Point sp1, sp2;

  regionQueue.push_back(this);
  while(!regionQueue.empty())
  {
    region = regionQueue.back();
    // calc the longest road edge and split size
    longestEdge = region->getLongestEdgeWithRoadAccess();
    edgeLine.set(longestEdge->begining, longestEdge->next->begining);
    if(edgeLine.length() < MAX_LOT_WIDTH)
    {
      // calc the longest non-road edge and split size
      longestEdge = region->getLongestEdgeWithoutRoadAccess();
      if(edgeLine.length() < MAX_LOT_DEPTH)
      {
        // if lot is small enough, add completed region
        outputRegions.push_back(region);
        regionQueue.pop_back();
        continue;
      }
      else
      {
        splitSize = MAX_LOT_DEPTH;
      }
    }
    else
    {
      splitSize = MAX_LOT_WIDTH;
    }
    // calculate the split points
    sp1 = calcSplitPoint(edgeLine, splitSize, LOT_DEVIANCE);
    sp2 = sp1 + edgeLine.normal();//*longestEdge.length();
    // split and process the new regions
    newRegions = splitRegion(region, sp1, sp2);
    regionQueue.pop_back();
    for (std::vector<Area*>::iterator newRegion = newRegions.begin();
         newRegion != newRegions.end();
         newRegion++)
    {
      if((*newRegion)->hasRoadAccess())
      {
        regionQueue.push_back(*newRegion);    // add to processing queue
      }
      else
      {
        delete *newRegion;                    // discard region
      }
    }
  }
}

Point Block::calcSplitPoint(LineSegment const& longestEdge, double splitSize, double lotDeviance)
{
  double factor, fraction, midPosition;

  factor = std::floor(longestEdge.length() / splitSize);
  fraction = 1/factor;
  midPosition = std::floor(factor/2) * fraction;

  // calculate longest edge vector src -> dst
  Vector longestEdgeDirection(longestEdge.begining(), longestEdge.end());
  Random numberGenerator;
  return longestEdge.begining() + longestEdgeDirection *
         (midPosition + (lotDeviance * (numberGenerator.generateDouble(0, 1) - 0.5) * fraction));
}

std::vector<Area*> Block::splitRegion(Area* area, Point a, Point b)
{
  Edge* region = area->getPolygonGraphCopy();
  Vector ab = b - a;
  double Lsq = ab.squaredLength();

  Edge* edge = region;
  while(edge->next != region)
  {
    Vector ac = edge->begining - a;
    edge->s = (-ac.y() * ab.x() + ac.x() * ab.y()) / Lsq;
    edge = edge->next;
  }

  double denom, r, s;
  Vector ca, cd;
  edge = region;
  Edge* intersection;
  std::list<Edge*> createdEdges;
  while(edge->next != region)
  {
    if((edge->s > 0 && edge->next->s <= 0)
      || (edge->s <= 0 && edge->next->s > 0))
    {
      cd = edge->next->begining - edge->begining;
      denom = (ab.x() * cd.y()) - (ab.y() * cd.x());
      ca = a - edge->begining;
      r = ((ca.y() * cd.x()) - (ca.x() * cd.y())) / denom;   // loc on ab
      s = ((ca.y() * ab.x()) - (ca.x() * ab.y())) / denom;   // loc on cd

      if(edge->s == 0)             // if split on src
      {
        intersection = edge;
      }
      else if(edge->next->s == 0) // if split on dst
      {
        intersection = edge->next;
      }
      else
      {
        // intersection point calc using cd, splitline ab is flat
        intersection = area->insertToPolygonGraph(edge, edge->begining + cd*s);
        intersection->hasRoadAccess = edge;
      }
      intersection->s = r;
      createdEdges.push_back(intersection);
    }
    edge = edge->next; // edge++;
  }

  // sort the created list by location on ab
  createdEdges.sort();

  // mark edges as unvisited
  edge = region;
  while(edge->next != region)
  {
    edge->s = 0;
    edge = edge->next;
  }


  // bridge intersection pairs
  assert(createdEdges.size() % 2 == 0);
  std::list<Edge*>::iterator last = --createdEdges.end();
  std::list<Edge*>::iterator next;
  for(std::list<Edge*>::iterator createdEdge = createdEdges.begin();
      createdEdge != last;
      createdEdge++, createdEdge++) /* Step by two */
  {
    next = createdEdge;
    next++;
    area->bridge(*createdEdge, *next);
  }

  // finally extract the new regions
  bool skipDuplicate;
  std::vector<Area*> outputRegions;
  Area* newRegion;
  for(std::list<Edge*>::iterator createdEdge = createdEdges.begin();
      createdEdge != createdEdges.end();
      createdEdge++)
  {
    edge = *createdEdge;
    skipDuplicate = false;
    do
    {
      if (edge->s > 0)
      {
        skipDuplicate = true;
        break;
      }
      edge->s = 1;            // mark edge as visited
      edge = edge->next;    // advance to next edge
    }
    while(edge != *createdEdge);
    if(!skipDuplicate)
    {
      newRegion = new Area;
      area->setParent(this);
      area->setAreaConstraints(edge);
      outputRegions.push_back(newRegion);
    }
  }

  return outputRegions;
}