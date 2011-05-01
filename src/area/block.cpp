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

#define NDEBUG
#include "../debug.h"

#include "../random.h"
#include "../geometry/units.h"
#include "../geometry/point.h"
#include "../geometry/polygon.h"
#include "../geometry/line.h"
#include "../geometry/vector.h"
#include "../geometry/linesegment.h"
#include "zone.h"
#include "lot.h"
#include "subregion.h"

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

void Block::createLots(double lotWidth, double lotHeight, double deviance)
{
  double LOT_WIDTH = lotWidth;
  double LOT_DEPTH = lotHeight;

  double LOT_DEVIANCE  = deviance;
  assert(deviance >= 0 && deviance <= 1);

  SubRegion* region; /* Current region. */
  std::vector<SubRegion*> regionQueue; /* Elements to be subdivided. */
  std::list<SubRegion*>   newRegions;  /* Newly added regions by splitRegion. */
  std::list<SubRegion*>   outputRegions; /* Regions that need no further subdivision. */
  SubRegion::Edge* longestEdge; /* Longest edge of current region. */
  LineSegment edgeLine;
  double splitSize;
  Point sp1, sp2; /* Split line. */

  /* A valid region must have at least 3 vertices. */
  assert(constraints->numberOfVertices() >= 3);

  /* Convert areaConstraints of this block to polygonGraph
     that is used in subdivision algorithm. */
  region = new SubRegion(*constraints);

  SubRegion::Edge* blockFirst = region->getFirstEdge();
  SubRegion::Edge* current = blockFirst;
  do /* All edges of Block has road access */
  {
    current->hasRoadAccess = true;
    current = current->next;
  }
  while (current != blockFirst);


  /* Add the region to queue for splitting */
  regionQueue.push_back(region);

  /* While there are some more regions to subdivide. */
  while(!regionQueue.empty())
  {
    /* Get first region. */
    region = regionQueue.back();

    /* Calc the longest road edge and split size. */
    longestEdge = region->getLongestEdgeWithRoadAccess();
    if (longestEdge != 0)
    {
      edgeLine.set(longestEdge->begining, longestEdge->next->begining);
      debug("Longest Road edge: " << edgeLine.length());
      if(edgeLine.length() <= LOT_WIDTH) /* No road edge requires further splitting. */
      {
        /* Calc the longest non-road edge and split size. */
        longestEdge = region->getLongestEdgeWithoutRoadAccess();
        if (longestEdge != 0)
        {
          edgeLine.set(longestEdge->begining, longestEdge->next->begining);
          debug("Longest NONRoad edge: " << edgeLine.length());
          if(edgeLine.length() <= LOT_DEPTH) /* No non-road edge requires further splitting. */
          {
            debug("Region is small enough, moving to output.");
            debug("  area = " << region->toPolygon().area());
            debug(region->toString());
            /* Region is complete. */
            outputRegions.push_back(region);
            regionQueue.pop_back();
            continue;
          }
          else
          {
            splitSize = LOT_DEPTH;
          }
        }
        else
        {
          /* All edges are small enough */
          outputRegions.push_back(region);
          regionQueue.pop_back();
          continue;
        }
      }
      else
      {
        splitSize = LOT_WIDTH;
      }
    }
    else
    {
      // if lot is small enough, add completed region
      debug("THIS REGION HAS NO Edge with RoadAccess.");
      debug("  " << region->toPolygon().toString());
      outputRegions.push_back(region);
      regionQueue.pop_back();
      continue;
    }

    // calculate the split points
    sp1 = calcSplitPoint(edgeLine, splitSize, LOT_DEVIANCE);
    sp2 = sp1 + edgeLine.normal();//*longestEdge.length();
    // split and process the new regions
    newRegions = splitRegion(region, sp1, sp2);
    regionQueue.pop_back();
    for (std::list<SubRegion*>::iterator newRegion = newRegions.begin();
         newRegion != newRegions.end();
         newRegion++)
    {
      debug("New region:");
      debug((*newRegion)->toString());
      if((*newRegion)->hasRoadAccess())
      {
        debug("  Adding to processing queue: " << (*newRegion)->toPolygon().toString());
        regionQueue.push_back(*newRegion);    // add to processing queue
      }
      else
      {
        debug("  Discarded.");
        delete *newRegion;                    // discard region
      }
    }
  }

  debug("Block::createLots() numberOfRegions " << outputRegions.size());
  for (std::list<SubRegion*>::iterator newRegion = outputRegions.begin();
      newRegion != outputRegions.end();
      newRegion++)
  {
    lots.push_back(new Lot(this, (*newRegion)->toPolygon()));
    delete *newRegion;
  }
}

Point Block::calcSplitPoint(LineSegment const& longestEdge, double splitSize, double lotDeviance)
{
  double factor, fraction, midPosition;

  debug("Block::calcSplitPoint() longestEdge.length() = " << longestEdge.length());
  factor = std::floor(longestEdge.length() / splitSize + 0.5);
  fraction = 1/factor;
  debug("Block::calcSplitPoint() factor = " << factor);
  midPosition = (factor/2) * fraction;
  debug("Block::calcSplitPoint() midPosition = " << midPosition);

  assert(midPosition > 0 && midPosition < 1);

  // calculate longest edge vector src -> dst
  Vector longestEdgeDirection(longestEdge.begining(), longestEdge.end());
  Random numberGenerator;

  Point retval = longestEdge.begining() + longestEdgeDirection *
         (midPosition + (lotDeviance * (numberGenerator.generateDouble(0, 1) - 0.5) * fraction));
  return retval;
}

std::list<SubRegion*> Block::splitRegion(SubRegion* area, Point a, Point b)
{
  SubRegion::Edge* region = area->getFirstEdge();
  Vector ab = b - a;
  double Lsq = ab.squaredLength();

  SubRegion::Edge* edge = region;
  do
  {
    Vector ac = edge->begining - a;
    edge->s = (-ac.y() * ab.x() + ac.x() * ab.y()) / Lsq;
    edge = edge->next;
  }
  while(edge != region);

  Vector ca, cd;
  SubRegion::Edge* intersection;
  std::list<SubRegion::Edge*> createdEdges;
  LineSegment::Intersection result;
  Line splitLine(a, b);
  LineSegment currentEdge;
  Point intersectionPoint;

  debug("SPLITTING AREA: ");
  debug(area->toString());

  edge = region;
  do
  {
    currentEdge.set(edge->begining, edge->next->begining);
    debug("-------------------");
    debug("splitLine " << splitLine.toString());
    debug("currentEdge " << currentEdge.toString());
    debug("Current edge roadAccess " << edge->hasRoadAccess);
    result = currentEdge.intersection2D(splitLine, &intersectionPoint);
    if (result == Line::INTERSECTING)
    {
      debug("Intersection at: " << intersectionPoint.toString());
      if (intersectionPoint == currentEdge.begining())
      {
        debug("New edge = current edge");
        intersection = edge;
        intersection->hasRoadAccess = edge->hasRoadAccess;
        createdEdges.push_back(intersection);
      }
      else if (intersectionPoint == currentEdge.end())
      {
        //intersection->hasRoadAccess = edge->next->hasRoadAccess;
        //intersection = edge->next;
      }
      else if (intersectionPoint != currentEdge.begining() &&
               intersectionPoint != currentEdge.end())
      {
        debug("begin diff x = " << intersectionPoint.x() - currentEdge.begining().x());
        debug("begin diff y = " << intersectionPoint.y() - currentEdge.begining().y());
        debug("end diff x = " << intersectionPoint.x() - currentEdge.end().x());
        debug("end diff y = " << intersectionPoint.y() - currentEdge.end().y());
        intersection = area->insert(edge, intersectionPoint);
        intersection->hasRoadAccess = edge->hasRoadAccess;
        createdEdges.push_back(intersection);
        edge = edge->next; // Jump over the just inserted area
      }
    }

    edge = edge->next; // edge++;
  }
  while(edge != region);

  // sort the created list by location on ab
  createdEdges.sort();

  // mark edges as unvisited
  edge = region;
  do
  {
    edge->s = 0;
    edge = edge->next;
  }
  while(edge != region);

  std::list<SubRegion*> outputRegions;

  debug("Created edges: " << createdEdges.size());
  if (createdEdges.size() % 2 != 0)
  {
    // There was a problem with a subdivision
    return outputRegions; // throw the block away
  }

  std::vector<SubRegion::Edge*> temporary;
  temporary.assign(createdEdges.begin(), createdEdges.end());
  for(unsigned int i = 0; i < temporary.size(); i += 2) /* Step by two */
  {
    area->bridge(temporary[i], temporary[i+1]);
  }

  // finally extract the new regions
  bool skipDuplicate;
  for(std::list<SubRegion::Edge*>::iterator createdEdge = createdEdges.begin();
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
      outputRegions.push_back(new SubRegion(edge));
    }
  }

  debug("Block::splitRegion(): returning regions: " << outputRegions.size());
  return outputRegions;
}

std::list<Lot*> Block::getLots()
{
  return lots;
}
