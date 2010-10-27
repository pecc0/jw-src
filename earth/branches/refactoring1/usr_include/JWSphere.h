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

using namespace irr;
using namespace __gnu_cxx;

namespace jw
{
/*
struct UnsignedHash
{
	size_t operator()(const u32 __s) const
	{
		return __s;
	}
};

struct UnsignedEquals
{
	size_t operator()(const u32& __x, const u32& __y) const
	{
		return __x == __y;
	}
};

typedef hash_map<u32, JWTriangle, UnsignedHash, UnsignedEquals> TrianglesMap;
*/


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
	AutoCleanHashMap<JWTriangle> m_vmapTriangles[14]; //14 levels of zoom
public:
	JWSphere();
	virtual ~JWSphere();

	core::vector3df* getVertex(u32 key);

	JWTriangle* getTriangle(u32 key, int level);

	/**
	 * Returns the global ID of a vertex in triangle
	 * \param triangle ID of a triangle
	 * \i internal ID of the vertex inside the triangle (0-2)
	 */
	u32 getTriangleVertex(u32 triangle, int level, int i);

	//void generate
};
}
#endif /* JWSPHERE_H_ */
