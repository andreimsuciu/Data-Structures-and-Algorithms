#pragma once
#include<iostream>
#include<string>
#include<vector>

typedef int TValue;
class SLLA;
class SMMIterator;
class SLLAv {
	friend class SLLA;
	friend class SortedMultiMap;
	friend class SMMIterator;
private:
	TValue *elems;
	int *next;
	int capacity;
	int head;
	int firstEmpty;
	int size;

public:
	//constructor
	SLLAv();
	//SLLAv(const SLLAv<TValue>& vector);
	//destructor
	~SLLAv();

	//dynamic vector functions. they return bool to know if the function succeeds
	void add(TValue elem);
	void remove(TValue elem);
	bool searchValue(TValue elem);

	int getSize() const { return this->size; }
	int getHead() const { return this->head; }
	int getNext(int pos) const { return this->next[pos]; }

	/* operator overload
	DynamicVector<TValue>& operator+(TValue elem);
	*/
};

//constructor

SLLAv::SLLAv() {
	this->capacity = 10;
	this->firstEmpty = 0;
	this->head = -1;
	this->elems = new TValue[10];
	this->next = new int[10];
	for (int i = 0; i < this->capacity - 1; i++)
		this->next[i] = i + 1;
	this->next[this->capacity] = -1;
	this->size = 0;
}

//we need destructor to free memory

SLLAv::~SLLAv() {
	delete[] this->elems;
	delete[] this->next;
}

//FUNCTIONS:

bool SLLAv::searchValue(TValue elem) {
	int current = this->head;
	while (current != -1 && this->elems[current] != elem)
		current = this->next[current];
	if (current != -1)
		return true;
	else
		return false;
}

void SLLAv::add(TValue elem) {
	if (this->firstEmpty == -1) {
		int newCapacity = this->capacity * 2;
		TValue *newElems = new TValue[newCapacity];
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

void SLLAv::remove(TValue elem) {
	int nodC = this->head;
	int prevNode = -1;
	while (nodC != -1 && this->elems[nodC] != elem) {
		prevNode = nodC;
		nodC = this->next[nodC];
	}
	if (nodC != -1) {
		if (nodC = this->head)
			this->head = this->next[this->head];
		else
			this->next[prevNode] = this->next[nodC];
		this->next[nodC] = this->firstEmpty;
		this->firstEmpty = nodC;
	}
	else
		throw std::range_error("Element does not exist!");
}


/*
//OPERATORS
template <typename TValue>
SLLAv<TValue>& SLLAv<TValue>::operator=(const SLLAv<TValue>& vector) {
	TValue *newElemVector, *newNextVector;

	this->capacity = vector.capacity;
	this->firstEmpty = vector.firstEmpty;
	this->head = vector.head;
	newElemVector = new TValue[this->capacity];
	newNextVector = new TValue[this->capacity];

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

template <typename TValue>
DynamicVector<TValue>& DynamicVector<TValue>::operator+(TValue elem)
{
	if (this->search(elem) == true)
		return *this;
	if (this->size == this->capacity)
	{
		TValue *newElems;

		this->capacity *= 2;
		newElems = new TValue[this->capacity];
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

template <typename TValue>
DynamicVector<TValue>::DynamicVector(const DynamicVector<TValue>& vector) {
	int i;

	this->capacity = vector.capacity;
	this->size = vector.size;
	this->elems = new TValue[this->capacity];
	for (i = 0; i < this->size; i++)
		this->elems[i] = vector.elems[i];
}
*/

