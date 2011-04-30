/**
 * This code is part of libcity library.
 *
 * @file areaextractor.h
 * @date 31.02.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @brief Class for extracting closed areas between roads in StreetGraph.
 *
 * Extract Zones and Blocks from StreetGraph.
 *
 * Takes a snapshot of the StreetGraph and then
 * finds all minimal cycles in the graph using
 * David Eberly's algorithm for planar graphs.
 *
 * @todo Might use some refactoring to make the class
 * more generic. Now it works with Intersection as a
 * node, which makes it unusable outside of a StreetGraph.
 * It could for example work with points as nodes.
 */

#include <list>
#include <set>
#include <map>
#include <vector>

#include "road.h"

class Intersection;
class Polygon;
class Zone;
class Block;
class StreetGraph;

class AreaExtractor
{
  public:
    /**
     * Creates a snapshot ofstreet graph from list of intersections.
     * Copying is neccessary, because the algorithm modifies
     * the graph as it goes. In the end the whole graph is
     * deleted.
     */
    AreaExtractor();
    ~AreaExtractor();

    AreaExtractor(AreaExtractor const& source);
    AreaExtractor& operator=(AreaExtractor const& source);

    void setRoadWidth(Road::Type type, double width);
    void setRoadWidths(std::map<Road::Type, double> widths);

    std::list<Zone*> extractZones(StreetGraph* fromMap, Zone* zoneConstraints = 0);
    std::list<Block*> extractBlocks(StreetGraph* fromMap, Zone* zoneConstraints = 0);

  private:
    Intersection* first(); /**< Get first node in sequence. */
    bool empty(); /**< Is graph empty? */

    /**
     * Find all minimal cycles and return them as polygons.
     */
    void getMinimalCycles();
    
    void minimalizeCycle(Polygon* minimalCycle, std::vector<double>* distances);
    std::vector<double> getSubstractDistances(std::vector<Intersection*> intersections);
    void substractRoadWidths(Polygon* minimalCycle, std::vector<double> const& distances);

    void copyVertices(StreetGraph* map, Zone* zone = 0);
    void addVertex(Intersection* node, Zone* zone = 0);
    void removeVertex(Intersection* node);

    /* Adding edges not neccessary */
    void removeEdge(Intersection* begining, Intersection* end);

    bool isCycleEdge(Intersection* begining, Intersection* end);
    void markCycleEdge(Intersection* begining, Intersection* end);

    /* Extracting methods. */
    void extractIsolatedVertex(Intersection* vertex);
    void extractFilament(Intersection* current, Intersection* next);
    void extractMinimalCycle(Intersection* current, Intersection* next);

    Intersection* getClockwiseMost(Intersection* previous, Intersection* current);
    Intersection* getCounterclockwiseMost(Intersection* previous, Intersection* current);

    /* Adjacent nodes access methods. */
    int numberOfAdjacentNodes(Intersection* node);
    std::vector<Intersection*> adjacent(Intersection* node);
    Intersection* firstAdjacentNode(Intersection* node);

    void initialize();
    void reset();
    void freeMemory();

    void dumpAdjacencyLists();
    void dumpAdjacenciesFromVertices();

  private:
    /** Stores all vertices of the graph sorted by their x position. */
    std::list<Intersection*>* vertices;

    /** Graph description. List of adjacent nodes to each node. */
    std::map< Intersection*, std::vector<Intersection*> >* adjacentNodes;

    /** Edges marked as a part of a cycle. */
    std::set< std::pair<Intersection*, Intersection*> > *cycleEdges;

    std::map<Road::Type, double> roadWidths;
    bool substractRoadWidthFromAreas;

    StreetGraph* map;

    std::list<Polygon>* cycles;
};