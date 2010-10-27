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
	bool
	(*m_fnIsForDelete)(KEY);
	D* m_ptrPool;
	KEY* m_ptrKeys;

	//Double liked list of indexes stuff
	int m_nFirst;
	int* m_prtPrev;
	int* m_prtNext;
public:

	/**
	 * \param size The size of the map
	 * \param collisionJump Number of positions to jump after a collision
	 * \param ptIsForDelete Predicate to quickly decide whether an element could be deleted by the element key.
	 */
	AutoCleanHashMap(int capacity = 1, int collisionJump = 1, bool(*ptIsForDelete)(
			KEY) = NULL) :
		m_nCapacity(capacity), m_nSize(0), m_nCollisionJump(collisionJump),
				m_fnIsForDelete(ptIsForDelete), m_nFirst(-1)

	{
		m_ptrPool = new D[m_nCapacity];
		m_ptrKeys = new KEY[m_nCapacity];

		memset(m_ptrKeys, EMPTY_KEY, m_nCapacity * sizeof(KEY));

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

	int size()
	{
		return m_nSize;
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

	void put(KEY key, D data) {
		put(key, &data);
	}

	void put(KEY key, D * data)
	{
		if (size() > (m_nCapacity * 8) / 10) { //After 80% the map starts to be unefective

		}
		int index = hash(key);
		if (m_nFirst == -1)
		{
			//TODO assert that m_nSize == 0
			m_nFirst = index;
			m_prtPrev[index] = index;
			m_prtNext[index] = index;
		}

		if (m_ptrKeys[index] == EMPTY_KEY)
		{
			//Element does not exist
			push(index);
			m_nSize++;
		}
		else
		{
			//We will replace existing element
			use(index);
		}
		m_ptrKeys[index] = key;
		m_ptrPool[index] = (*data);
	}

	/**
	 * Returns pointer to the object which corresponds to certain key. The object is moved to the beginning of the DL list and will not be deleted soon
	 */
	D* get(KEY key)
	{
		int index = hash(key);
		if (m_ptrKeys[index] == EMPTY_KEY)
		{
			return NULL;
		}
		use(index);
		return m_ptrPool + index;
	}

	void deleteLast(int num) {
		Iterator i = begin();
		i--;
		while (num > 0) {
			int current = i.Current;
			if (current == m_nFirst) {
				//We reached the start of the list.
				return;
			}
			i--;
			if (!m_fnIsForDelete || (*m_fnIsForDelete) (m_ptrKeys[current])) {
				dlListDelete(current);
				m_ptrKeys[current] = EMPTY_KEY;
				//delete (m_ptrPool + current);
				//TODO call the destructor of the object
				--m_nSize;
				--num;
			}
		}
	}

	/**
	 * Removes an entry from the DL List
	 */
    void dlListDelete(int & index)
    {
        int prev = m_prtPrev[index];
        int next = m_prtNext[index];
        m_prtNext[prev] = next;
        m_prtPrev[next] = prev;
    }

    /**
	 * Move the index to the beginning if the list
	 */
    void use(int index)
    {
        if(m_nFirst == index){
            //element is already in the beginning;
            return;
        }
        dlListDelete(index);
        push(index);
    }

    /**
	 * Adds the index to the beginning if the list
	 */
    void push(int index)
    {
        int last = m_prtPrev[m_nFirst];
        m_prtNext[index] = m_nFirst;
        m_prtPrev[index] = last;
        m_prtNext[last] = index;
        m_prtPrev[m_nFirst] = index;
        m_nFirst = index;
    }

    class Iterator
    {
    public:
        Iterator()
        :Current(0)
        {
        }

        Iterator & operator ++()
        {
            Current = HashMap->m_prtNext[Current];
            return *this;
        }

        Iterator & operator --()
        {
            Current = HashMap->m_prtPrev[Current];
            return *this;
        }

        Iterator operator ++(int)
        {
            Iterator tmp = *this;
            Current = HashMap->m_prtNext[Current];
            return tmp;
        }

        Iterator operator --(int)
        {
            Iterator tmp = *this;
            Current = HashMap->m_prtPrev[Current];
            return tmp;
        }

        Iterator & operator +=(int num)
        {
            if(num > 0){
                while(num-- && this->Current != -1)
                    ++(*this);

            }else{
                while(num++ && this->Current != -1)
                    --(*this);

            }
            return *this;
        }

        Iterator operator +(int num) const
        {
            Iterator tmp = *this;
            return tmp += num;
        }

        Iterator & operator -=(int num)
        {
            return (*this) += (-num);
        }

        Iterator operator -(int num) const
        {
            return (*this) + (-num);
        }

#if defined (_MSC_VER) && (_MSC_VER < 1300)
#pragma warning(disable:4284) // infix notation problem when using iterator operator ->
#endif
        D & operator *()
		{
			return HashMap->m_ptrPool[Current];
		}

		D * operator ->()
		{
			return HashMap->m_ptrPool + Current;
		}

	private:
		explicit Iterator(AutoCleanHashMap * hashMap, int begin) :
			Current(begin), HashMap(hashMap)
		{
		}

		int Current;
		AutoCleanHashMap * HashMap;

		friend class AutoCleanHashMap<D> ;
	};

	Iterator begin()
	{
		return Iterator(this, m_nFirst);
	}
};

}

#endif /* DECAPSULATEDHASHTABLE_H_ */