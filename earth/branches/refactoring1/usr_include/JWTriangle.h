/*
 * JWTriangle.h
 *
 *  Created on: Oct 19, 2010
 *      Author: Petko
 */

#ifndef JWTRIANGLE_H_
#define JWTRIANGLE_H_

#include "irrTypes.h"

using namespace irr;

/**
 * We will tessellate the earth into triangles. We start the tessellation from an octahedron.
 * Then we start to recursively divide each of the triangles into 4 little triangles.
 * The "history" of each received triangle is stored into its TrIndex field. The first 8 triangles
 * of the octahedron has TrIndex 0b000 - 0b111. Then at each iteration, we occupy 2 more bits
 * of the u32 type. The child triangles are numbered 0b00 - 0b11. The center triangle is
 * always 0b11, the other triangles are numbered according to the vertex they share with
 * the parent. The level of the triangle is the iteration at which we have received the
 * triangle. The triangles of the octahedron have level=0. We don't store this value because
 * it is too common and we could take it from outside. A triangle is considered
 * "upside" if 1 of its edges is above the 2 others. 4 of the octahedron triangles are "upside".
 * When we divide a triangle, only the central one changes its direction.
 * So we can easily determine whether a triangle is upside by having its TrIndex and its level.
 * In m_vNeighbours we store the indexes of the neighbour triangles.
 *
 * @see JWTriangle::isUpside
 */
class JWTriangle
{
	u32 m_u32TrIndex;
	/**
	 * indexes of the neighbour triangles
	 */
	u32 m_vNeighbours[3];
public:
	JWTriangle();
	JWTriangle(u32 indx, u32 ngh0, u32 ngh1, u32 ngh2);
	virtual ~JWTriangle();
	/**
	 * Returns the index of the triangle. This value contains the "history" of the triangle. See
	 * JWTriangle
	 */
	u32 getTrIndex() const;
	void setTileIndex(u32 TileIndex);

	/**
	 * Set the IDs of neighbour triangles.
	 * Watch out: if you know ID of triangle one level above the current,
	 * you must also set the 1st bit of the u32 you give
	 */
	void setNeighbours(u32 v0, u32 v1, u32 v2);

	/**
	 * Returns the ID of a neighbour triangle.
	 * It is possible that the triangle is not from the same level, but one level above.
	 * This is stored in the first bit of the triangle ID. Use
	 * sNeighbourGenerated to check whether the neighbour is from same level
	 * \param i internal index of the neighbour - 0-2
	 */
	u32 getNeighbour(int i);

	/**
	 * Returns whether the ID of neighbour we have is a triangle from same level,
	 * or from one level above
	 *  \param i internal index of the neighbour - 0-2
	 */
	bool isNeighbourGenerated(int i);
	/**
	 * Returnes whether a triangle is "upside". A triangle is considered "upside" if 1 of his edges is above the 2 others.
	 */
	bool isUpside(int level);

};

#endif /* JWTRIANGLE_H_ */
