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

class JWTriangle {
	u32 TrIndex;
	u32 Neighbours[3];
public:
	JWTriangle();
	JWTriangle(u32 v0, u32 v1, u32 v2);
	virtual ~JWTriangle();
    u32 getTileIndex() const;
    void setTileIndex(u32 TileIndex);
    void setNeighbours(u32 v0, u32 v1, u32 v2);
    u32 getNeighbour(int i);
};

#endif /* JWTRIANGLE_H_ */
