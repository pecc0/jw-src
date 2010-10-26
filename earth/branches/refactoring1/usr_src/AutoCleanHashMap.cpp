/*
 * DecapsulatedHashtable.cpp
 *
 *  Created on: Oct 25, 2010
 *      Author: PetkoLtd
 */

#include "AutoCleanHashMap.h"

namespace jw {

template<class K, class D> AutoCleanHashMap<K, D>::AutoCleanHashMap(int size, int collisionJump) : AutoCleanHashMap(size, collisionJump, NULL)
{
}

template<class K, class D> AutoCleanHashMap<K, D>::AutoCleanHashMap(int size) : AutoCleanHashMap(size, 1)
{
}

template<class K, class D> AutoCleanHashMap<K, D>::AutoCleanHashMap(int size, int collisionJump, bool (*ptIsForDelete)(K))
{
	m_nSize = size;

}

template<class K, class D> AutoCleanHashMap<K, D>::~AutoCleanHashMap() {
	// TODO Auto-generated destructor stub
}

}
