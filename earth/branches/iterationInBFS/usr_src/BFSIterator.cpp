/*
 * BFSIterator.cpp
 *
 *  Created on: Nov 11, 2010
 *      Author: PetkoLtd
 */

#include "JWSphere.h"

namespace jw
{

BFSIterator::BFSIterator(JWSphere* sphere, int level, u32 marker) :
	m_sphere(sphere), m_level(level), m_Iteration(0), m_trMarker(marker)
{

}

BFSIterator::BFSIterator(JWSphere* sphere, u32 start, int level) :
	m_sphere(sphere), m_level(level), m_Iteration(0), m_trMarker(start)
{
	start = JWTriangle::cropToLevel(start, level);
	push(start);
	setUsed(start);
}

BFSIterator::BFSIterator(BFSIterator * old, int level) :
	m_sphere(old->m_sphere), m_level(level)
{

}

bool BFSIterator::isUsed(u32 tr)
{
	return m_trUsed.find(tr) != m_trUsed.end();
}

void BFSIterator::setUsed(u32 tr)
{
	m_trUsed.insert(tr);
}

bool BFSIterator::isInQueue(u32 tr)
{

	deque<u32>::iterator i;
	//I'm sorry
	for (i = m_trQueue.begin(); i != m_trQueue.end(); i++)
	{
		if (*i == tr)
		{
			return true;
		}
	}
	return false;
}

void BFSIterator::push(u32 triangle)
{
	m_trQueue.push_front(triangle);
}

int BFSIterator::getLevel() const
{
	return m_level;
}

void BFSIterator::setLevel(int m_level)
{
	this->m_level = m_level;
}

bool BFSIterator::next(u32* result)
{
	if (m_trQueue.empty())
	{
		return false;
	}
	*result = m_trQueue.back();
	m_trQueue.pop_back();

	return true;
}

bool BFSIterator::accept(u32 triangle)
{
	bool result = false;
	JWTriangle* tr = m_sphere->getTriangle(triangle, m_level);
	for (int i = 0; i < 3; i++)
	{
		u32 neigh = tr->getNeighbour(i);

		if (!isUsed(neigh))
		{
			if (triangle == m_trMarker)
			{
				m_trMarker = neigh;
				++m_Iteration;
			}
			push(neigh);
			setUsed(neigh);
			result = true;
		}
	}
	return result;
}

int BFSIterator::getIteration()
{
	return m_Iteration;
}

u32 BFSIterator::getMarker()
{
	return m_trMarker;
}
void BFSIterator::setMarker(u32 newMarker) {
	m_trMarker = newMarker;
}
}
