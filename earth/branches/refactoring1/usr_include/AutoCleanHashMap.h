/*
 * DecapsulatedHashtable.h
 *
 *  Created on: Oct 25, 2010
 *      Author: PetkoLtd
 */

#ifndef DECAPSULATEDHASHTABLE_H_
#define DECAPSULATEDHASHTABLE_H_

#include <stddef.h>

namespace jw {
//prime number
//#define UNDE 131072
//#define SIZE 1046527


template<class K, class D>
class AutoCleanHashMap {
	int m_nSize;
	int m_nUndeletable;
	D* m_ptrPool;
public:
	/**
	 * \param size The size of the map
	 */
	AutoCleanHashMap(int size);

	/**
	 * \param size The size of the map
	 * \param collisionJump Number of positions to jump after a collision
	 */
	AutoCleanHashMap(int size, int collisionJump);

	/**
	 * \param size The size of the map
	 * \param collisionJump Number of positions to jump after a collision
	 * \param ptIsForDelete Predicate to quickly decide whether an element could be deleted by the element key.
	 */
	AutoCleanHashMap(int size, int collisionJump, bool(*ptIsForDelete)(K));
	virtual ~AutoCleanHashMap();
};

}

#endif /* DECAPSULATEDHASHTABLE_H_ */
