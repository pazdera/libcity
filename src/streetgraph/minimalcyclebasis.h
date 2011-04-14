/**
 * This code is part of libcity library.
 *
 * @file minimalcyclebasis.h
 * @date 31.02.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @brief Minimal cycle basis algorithm.
 *
 * Takes a snapshot of the StreetGraph and then
 * finds all minimal cycles in the graph using
 * David Eberly's algorithm for planar graphs.
 *
 * \TODO Might use some refactoring to make the class
 * more generic. Now it works with Intersection as a
 * node, which makes it unusable outside of a StreetGraph.
 * It could for example work with points as nodes.
 */

class Intersection;
class Polygon;

#include <list>
#include <set>
#include <map>
#include <vector>

class MinimalCycleBasis
{
  public:
    /**
     * Creates a snapshot ofstreet graph from list of intersections.
     * Copying is neccessary, because the algorithm modifies
     * the graph as it goes. In the end the whole graph is
     * deleted.
     */
    MinimalCycleBasis(std::list<Intersection*>* inputIntersections);
    ~MinimalCycleBasis();

    MinimalCycleBasis(MinimalCycleBasis const& source);
    MinimalCycleBasis& operator=(MinimalCycleBasis const& source);

    /**
     * Find all minimal cycles and return them as polygons.
     */
    std::list<Polygon> getMinimalCycles();

  private:
    Intersection* first(); /**< Get first node in sequence. */
    bool empty(); /**< Is graph empty? */

    void addVertex(Intersection* node);
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

    std::list<Polygon>* cycles;
};