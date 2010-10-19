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
	u32 TileIndex;
	u16 VertexIndexes[3];
public:
	JWTriangle();
	JWTriangle(u16 v0, u16 v1, u16 v2);
	virtual ~JWTriangle();
    u32 getTileIndex() const;
    void setTileIndex(u32 TileIndex);
    void setVertexIndexes(u16 v0, u16 v1, u16 v2);
};

#endif /* JWTRIANGLE_H_ */
