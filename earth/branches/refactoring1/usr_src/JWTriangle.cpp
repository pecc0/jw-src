/*
 * JWTriangle.cpp
 *
 *  Created on: Oct 19, 2010
 *      Author: Petko
 */

#include "JWTriangle.h"

JWTriangle::JWTriangle()
{
}
JWTriangle::JWTriangle(u32 indx, u32 ngh0, u32 ngh1, u32 ngh2)
{
	setTileIndex(indx);
	setNeighbours(ngh0, ngh1, ngh2);
}

u32 JWTriangle::getTrIndex() const
{
	return m_u32TrIndex;
}

void JWTriangle::setTileIndex(u32 TileIndex)
{
	this->m_u32TrIndex = TileIndex;
}

void JWTriangle::setNeighbor(u32 ngh, int i)
{
	this->m_vNeighbours[i] = ngh;
}

void JWTriangle::setNeighbours(u32 v0, u32 v1, u32 v2)
{
	this->m_vNeighbours[0] = v0;
	this->m_vNeighbours[1] = v1;
	this->m_vNeighbours[2] = v2;
}

JWTriangle::~JWTriangle()
{
	// TODO Auto-generated destructor stub
}

u32 JWTriangle::getNeighbour(int i)
{
	return this->m_vNeighbours[i % 3] & 0xEFFFFFFF;
}

bool JWTriangle::isNeighbourGenerated(int i)
{
	return !(this->m_vNeighbours[i % 3] & 0xA0000000);
}

int JWTriangle::getNeighborInternalIndex(u32 trNeighbor)
{
	int result;
	for (result = 0; result < 3; result++)
	{
		if (getNeighbour(result) == trNeighbor)
		{
			return result;
		}
	}
	return -1;
}

bool JWTriangle::isUpside(int level)
{
	bool result = (m_u32TrIndex & 0b100) == 0;
	int i = level;
	while (i > 0)
	{
		//i * 2 + 1 = 3 + (i - 1) * 2
		if ((m_u32TrIndex >> (i * 2 + 1) & 0b11) == 0b11)
		{
			result = !result;
		}
		--i;
	}
	return result;
}



u32 JWTriangle::getChildIndex(u32 internalChildIndex, int level)
{
	return m_u32TrIndex | (internalChildIndex << (level * 2 + 3));
}





