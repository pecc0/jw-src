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
	int Iteration;
	u32 TrIndex;
	u32 Neighbours[3];
public:
	JWTriangle();
	JWTriangle(u32 indx, u32 v0, u32 v1, u32 v2);
	virtual ~JWTriangle();
    u32 getTrIndex() const;
    void setTileIndex(u32 TileIndex);
    void setNeighbours(u32 v0, u32 v1, u32 v2);
    u32 getNeighbour(int i);
    bool isUpside();
    int getIteration() const;
    void setIteration(int Iteration);
};

#endif /* JWTRIANGLE_H_ */
