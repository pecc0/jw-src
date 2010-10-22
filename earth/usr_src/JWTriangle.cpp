/*
 * JWTriangle.cpp
 *
 *  Created on: Oct 19, 2010
 *      Author: Petko
 */

#include "JWTriangle.h"

JWTriangle::JWTriangle() {
	Iteration = 0;
}
JWTriangle::JWTriangle(u32 indx, u32 v0, u32 v1, u32 v2) {
	setTileIndex(indx);
	setNeighbours(v0, v1, v2);
}


u32 JWTriangle::getTrIndex() const
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

int JWTriangle::getIteration() const
{
    return Iteration;
}

void JWTriangle::setIteration(int Iteration)
{
    this->Iteration = Iteration;
}

bool JWTriangle::isUpside()
{
	bool result = (TrIndex & 0b100) == 0;
	int i = Iteration;
	while (i > 0) {
		if ((TrIndex >> (3 + (i - 1) * 2) & 0b11) == 0b11) {
			result = !result;
		}
		i++;
	}
	return result;
}




