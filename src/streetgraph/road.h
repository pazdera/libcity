/**
 * This code is part of libcity library.
 *
 * @file streetgraph/road.h
 * @date 02.03.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @brief Base class for road representation
 *
 */

#ifndef _ROAD_H_
#define _ROAD_H_

#include <string>

class LineSegment;
class Intersection;
class Path;

class Road
{
  public:
    typedef unsigned short Type;
    static Type defineNewRoadType();

    /* Available built-in types. */
    /* These must be initialized to UNIQUE values. */
    static const Type PRIMARY_ROAD   = 0;
    static const Type SECONDARY_ROAD = 1;

    virtual Type type();
    virtual void setType(Type type);

    /** Create road between two intersections.
        Path is determined automaticaly.*/
    Road();
    Road(Intersection *first, Intersection *second);

    /**
     * Create just path of the road.
     **/
    Road(Path const& path);
    virtual ~Road();

    Intersection* begining() const;
    Intersection* end() const;

    void setBegining(Intersection* intersection);
    void setEnd(Intersection* intersection);

    Path* path() const;
    void setPath(Path const& roadPath) throw();

    std::string toString();

  private:
    /** Must be initialized to a proper value.
    There are TWO predefined road types. So in this case
    it ought be set to a number above 2. */
    static Type numberOfDefinedRoadTypes;

    /* Topological information */
    Intersection* from; /**< Where the road starts. */
    Intersection* to;   /**< Where it leads to. */

    /* Geometrical information */
    Path* geometrical_path; /**< Path that the road takes between the two topological points */

    Type roadType;

    void estimatePath();
};

/* Inlines */
inline Intersection* Road::begining() const
{
  return from;
}

inline Intersection* Road::end() const
{
  return to;
}


#endif
