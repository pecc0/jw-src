/*
 * JWSphere.h
 *
 *  Created on: Oct 26, 2010
 *      Author: Petko
 */

#ifndef JWSPHERE_H_
#define JWSPHERE_H_

#include <irrlicht.h>
#include "AutoCleanHashMap.h"
#include "JWTriangle.h"
#include "IJWLogger.h"

using namespace irr;

#define MAX_TRIANGLE_LEVELS 14

namespace jw
{

using namespace log;

/**
 * We will tessellate the sphere into triangles. We start the tessellation from an octahedron.
 * Then we start to recursively divide each of the triangles into 4 little triangles.
 * We have a clever style of indexing the triangles - see JWTriangle. We must also store
 * the vertexes of the mesh, but they are only linked functionally to the triangles.
 * For each triangle, we store only its neighbor triangles, ordered 0-2. We number the edges
 * of the triangle again with 0-2, and according to the index of the neighbour with which the
 * edge is shared. We internally number the vertexes of the triangle with 0-2, so that
 * the internal index of the vertex is equal to the index of the edge counter clockwise
 * from the vertex. We globally index the vertextes in following way:
 * The vertex receives its index from the triangle for which this vertex is at number 0 in the
 * internal numbering. In most cases, there are 2 triangles for which the vertex is at number 0.
 * So then we choose the triangle which is "upside" (see JWTriangle::isUpside). We choose
 * the initial octahedron so that there isn't a vertex with 2 upside triangles for which the
 * vertex is 0. This is possible. At next iterations, it is always true that if there are 2
 * triangles for which the vertex is at 0, one of them is upside, the other is not.
 */

class JWSphere
{
	AutoCleanHashMap<core::vector3df> m_mapVertices;
	AutoCleanHashMap<JWTriangle> m_vmapTriangles[MAX_TRIANGLE_LEVELS]; //14 levels of zoom
	IJWLogger * log;

	/**
	 * Returns a neighbour of a certain triangle. If the neighbour is not yet generated,
	 * will divide its parent. We always have the parent, or the neighbour itself in
	 * JWTriangle::m_vNeighbours.
	 * \param triangle Triangle whose neighbour we search.
	 * It must be pointer to triangle in m_vmapTriangles
	 * \param level Level where actions take place.
	 * \edge Internal (in our triangle edges) index of the edge which is shared
	 * between our thrianlge and the neighbour
	 */
	JWTriangle* getTrNeighbour(JWTriangle* triangle, int level, int edge);

public:
	JWSphere();
	virtual ~JWSphere();

	core::vector3df* getVertex(u32 key);

	JWTriangle* getTriangle(u32 key, int level);

	/**
	 * Returns the global ID of a vertex in triangle
	 * \param triangle ID of a triangle
	 * \param level
	 * \param i internal ID of the vertex inside the triangle (0-2)
	 */
	u32 getTriangleVertex(u32 triangle, int level, int i);

	void divideTriangle(u32 triangle, int level);

};
}
#endif /* JWSPHERE_H_ */
