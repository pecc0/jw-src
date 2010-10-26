/*
 * DecapsulatedHashtable.h
 *
 *  Created on: Oct 25, 2010
 *      Author: PetkoLtd
 */

#ifndef DECAPSULATEDHASHTABLE_H_
#define DECAPSULATEDHASHTABLE_H_

#include <stddef.h>
#include "string.h"

namespace jw
{
//prime number
//#define UNDE 131072
//#define SIZE 1046527

typedef unsigned int KEY;

#define EMPTY_KEY 0xFFFFFFFF

template<class D>
class AutoCleanHashMap
{
	int m_nCapacity;
	int m_nSize;
	int m_nCollisionJump;
	bool (*m_fnIsForDelete)(KEY);
	D* m_ptrPool;
	KEY* m_ptrKeys;

	//Double liked list of indexes stuff
	int m_nFirst;
	int m_nLast;
	int* m_prtPrev;
	int* m_prtNext;
public:

	/**
	 * \param size The size of the map
	 * \param collisionJump Number of positions to jump after a collision
	 * \param ptIsForDelete Predicate to quickly decide whether an element could be deleted by the element key.
	 */
	AutoCleanHashMap(int capacity, int collisionJump = 1, bool(*ptIsForDelete)(
			KEY) = NULL)
	{
		m_nSize = 0;
		m_nCapacity = capacity;
		m_nCollisionJump = collisionJump;
		m_fnIsForDelete = ptIsForDelete;
		m_ptrPool = new D[m_nCapacity];
		m_ptrKeys = new KEY[m_nCapacity];

		memset(m_ptrKeys, EMPTY_KEY, m_nCapacity * sizeof(KEY));

		m_nFirst = -1;
		m_nLast = -1;
		m_prtPrev = new int[m_nCapacity];
		memset(m_prtPrev, 0xFFFFFFFF, m_nCapacity * sizeof(int));
		m_prtNext = new int[m_nCapacity];
		memset(m_prtNext, 0xFFFFFFFF, m_nCapacity * sizeof(int));
	}
	virtual ~AutoCleanHashMap()
	{
		delete[] m_ptrPool;
		delete[] m_ptrKeys;
		delete[] m_prtPrev;
		delete[] m_prtNext;
	}

	int hash(KEY key)
	{
		int result = key % m_nCapacity;
		do
		{
			KEY keyInMap = m_ptrKeys[result];
			if (keyInMap == EMPTY_KEY || keyInMap == key)
			{
				return result;
			}
			else
			{
				result += m_nCollisionJump;
				result %= m_nCapacity;
			}
		} while (true);
	}

	/**
	 * Move the index to the beginning if the list
	 */
	void use(int index)
	{
		int prev = m_prtPrev[index];

		if (prev == -1)
		{
			//element is already in the beginning;
			return;
		}
		int next = m_prtNext[index];
		m_prtNext[prev] = next;
		if (next == -1) {
			//if the element is last
			m_nLast = prev;
		} else {
			m_prtPrev[next] = prev;
		}
		m_prtNext[index] = m_nFirst;
		m_nFirst = index;
	}
};

}

#endif /* DECAPSULATEDHASHTABLE_H_ */
