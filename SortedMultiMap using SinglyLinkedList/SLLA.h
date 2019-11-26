#pragma once
#include<iostream>
#include<string>
#include<vector>

#include "SLLAv.h"

typedef int TKey;
typedef int TValue;
typedef SLLAv values;
typedef std::pair<TKey, values> TElem;
class SortedMultiMap;
class SLLAv;
class SMMIterator;

class SLLA {
	friend class SortedMultiMap;
	friend class SLLAv;
	friend class SMMIterator;
private:
	TElem *elems;
	int *next;
	int capacity;
	int head;
	int firstEmpty;
	int size;
	
public:
	//constructor
	SLLA();
	//SLLA(const SLLA<TElem>& vector);
	//destructor
	~SLLA();

	//dynamic vector functions. they return bool to know if the function succeeds
	void add(TElem elem);
	void insertPosition(TValue value, int pos);
	void remove(TKey key, TValue value);
	int searchKey(TKey key);
};

//constructor
SLLA::SLLA() {
	this->capacity = 10;
	this->firstEmpty = 0;
	this->head = -1;
	this->elems = new TElem[10];
	this->next = new int[10];
	for (int i = 0; i < this->capacity - 1; i++)
		this->next[i] = i+1;
	this->next[this->capacity] = -1;
	this->size = 0;
}

//we need destructor to free memory

SLLA::~SLLA() {
	delete [] this->elems;
	delete [] this->next;
}

//FUNCTIONS:

int SLLA::searchKey(TKey key) {
	int current = this->head;
	while (current != -1 && this->elems[current].first != key)
		current = this->next[current];
	return current;
}


void SLLA::insertPosition(TValue value, int pos) {
	if (pos<0)
		throw std::range_error("Position must be positive!");
	if (this->firstEmpty == -1) {
		int newCapacity = this->capacity * 2;
		TElem *newElems = new TElem[newCapacity];
		int *newNext = new int[newCapacity];
		for (int i = 0; i < this->capacity; i++) {
			newElems[i] = this->elems[i];
			newNext[i] = this->next[i];
		}
		for (int i = this->capacity + 1; i <= newCapacity - 1; i++)
			newNext[i] = i + 1;
		newNext[newCapacity] = -1;
		delete[] this->elems;
		delete[] this->next;
		this->elems = newElems;
		this->next = newNext;
		this->firstEmpty = this->capacity + 1;
		this->capacity = newCapacity;
	}
	if (pos == -1) {
		/*
		int newPos = this->firstEmpty;
		this->elems[newPos] = value;
		this->firstEmpty = this->next[this->firstEmpty];
		this->next[newPos] = this->head;
		this->head = newPos;
		*/
	}
	else {
		int currentPos = 0;
		int currentNode = this->head;
		while (currentNode != -1 && currentPos < pos - 1) {
			currentPos++;
			currentNode = this->next[currentNode];
		}
		if (currentNode != -1) {
			this->elems[currentNode].second.add(value);
			this->size++;
			/*
			int newElem = this->firstEmpty;
			this->firstEmpty = this->next[firstEmpty];
			this->elems[newElem] = elem;
			this->next[newElem] = this->next[currentNode];
			this->next[currentNode] = newElem;
			*/
		}
		else
			throw std::range_error("Invalid position!");
	}
}

void SLLA::add(TElem elem) {
	if (this->firstEmpty == -1) {
		int newCapacity = this->capacity * 2;
		TElem *newElems = new TElem[newCapacity];
		int *newNext = new int[newCapacity];
		for (int i = 0; i < this->capacity; i++) {
			newElems[i] = this->elems[i];
			newNext[i] = this->next[i];
		}
		for (int i = this->capacity + 1; i <= newCapacity - 1; i++)
			newNext[i] = i + 1;
		newNext[newCapacity] = -1;
		this->elems = newElems;
		this->next = newNext;
		this->firstEmpty = this->capacity + 1;
		this->capacity = newCapacity;
	}
	
	int currentPos = 0;
	int currentNode = this->head;
	while (currentNode != -1 && this->next[currentNode] == -1) {
		currentPos++;
		currentNode = this->next[currentNode];
	}
	if (currentNode != -1) {
		int newElem = this->firstEmpty;
		this->firstEmpty = this->next[firstEmpty];
		this->elems[newElem] = elem;
		this->next[newElem] = this->next[currentNode];
		this->next[currentNode] = newElem;
		this->size++;
	}
	else
		throw std::range_error("Invalid position!");
}

void SLLA::remove(TKey key, TValue value) {
	int nodC = this->head;
	int prevNode = -1;
	while (nodC != -1 && this->elems[nodC].first != key) {
		prevNode = nodC;
		nodC = this->next[nodC];
	}
	if (nodC != -1 && this->elems[nodC].second.size<2) {
		if (nodC = this->head)
			this->head = this->next[this->head];
		else
			this->next[prevNode] = this->next[nodC];
		this->next[nodC] = this->firstEmpty;
		this->firstEmpty = nodC;
		this->size--;
	}
	else if (nodC!=-1 && this->elems[nodC].second.size>=2) {
		this->elems[nodC].second.remove(value);
	}
	else
		throw std::range_error("Element does not exist!");
}

/*
//OPERATORS

template <typename TElem>
SLLA<TElem>& SLLA<TElem>::operator=(const SLLA<TElem>& vector) {
	TElem *newElemVector;
	int *newNextVector;

	this->capacity = vector.capacity;
	this->firstEmpty = vector.firstEmpty;
	this->head = vector.head;
	newElemVector = new TElem[this->capacity];
	newNextVector = new int[this->capacity];

	for (int i = 0; i < this->capacity; i++) {
		newElemVector[i] = vector.elems[i];
		newNextVector[i] = vector.next[i];
	}
	delete[] this->elems;
	delete[] this->next;
	this->elems = nullptr;
	this->next = nullptr;
	this->elems = newElemVector;
	this->next = newNextVector;
	return *this;
}

template <typename TElem>
DynamicVector<TElem>& DynamicVector<TElem>::operator+(TElem elem)
{
	if (this->search(elem) == true)
		return *this;
	if (this->size == this->capacity)
	{
		TElem *newElems;

		this->capacity *= 2;
		newElems = new TElem[this->capacity];
		for (int i = 0; i < this->size; i++)
		{
			newElems[i] = this->elems[i];
		}
		delete[] this->elems;
		this->elems = newElems;
	}
	this->elems[this->size] = elem;
	this->size += 1;
	return *this;
}

template <typename TElem>
DynamicVector<TElem>::DynamicVector(const DynamicVector<TElem>& vector) {
	int i;

	this->capacity = vector.capacity;
	this->size = vector.size;
	this->elems = new TElem[this->capacity];
	for (i = 0; i < this->size; i++)
		this->elems[i] = vector.elems[i];
}
*/

