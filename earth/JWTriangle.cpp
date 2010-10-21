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
JWTriangle::JWTriangle(u32 indx, u32 v0, u32 v1, u32 v2) {
	setTileIndex(indx);
	setNeighbours(v0, v1, v2);
}


u32 JWTriangle::getTileIndex() const
{
    return TrIndex;
}

void JWTriangle::setTileIndex(u32 TileIndex)
{
    this->TrIndex = TileIndex;
}


void JWTriangle::setNeighbours(u32 v0, u32 v1, u32 v2)
{
    this->Neighbours[0] = v0;
    this->Neighbours[1] = v1;
    this->Neighbours[2] = v2;
}

JWTriangle::~JWTriangle() {
	// TODO Auto-generated destructor stub
}

u32 JWTriangle::getNeighbour(int i)
{
	return this->Neighbours[i % 3];
}


