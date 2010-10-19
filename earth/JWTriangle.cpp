/*
 * JWTriangle.cpp
 *
 *  Created on: Oct 19, 2010
 *      Author: Petko
 */

#include "JWTriangle.h"

JWTriangle::JWTriangle() {
	// TODO Auto-generated constructor stub

}
JWTriangle::JWTriangle(u16 v0, u16 v1, u16 v2) {
	setVertexIndexes(v0, v1, v2);
}


u32 JWTriangle::getTileIndex() const
{
    return TileIndex;
}

void JWTriangle::setTileIndex(u32 TileIndex)
{
    this->TileIndex = TileIndex;
}


void JWTriangle::setVertexIndexes(u16 v0, u16 v1, u16 v2)
{
    this->VertexIndexes[0] = v0;
    this->VertexIndexes[1] = v1;
    this->VertexIndexes[2] = v2;
}

JWTriangle::~JWTriangle() {
	// TODO Auto-generated destructor stub
}
