#include "SortedMultiMap.h"
#include <stdexcept>

SortedMultiMap::SortedMultiMap(Relation r) {
	this->rel = r;
	this->elems = new SLLA;
	this->s = 0;
}

SortedMultiMap::~SortedMultiMap() {
}

void SortedMultiMap::add(TKey c, TValue v) {
	int pos = this->elems->searchKey(c);
	if (pos != -1) {
		this->elems->insertPosition(v, pos);
		this->s++;
	}
	else {
		SLLAv *values=new SLLAv;
		values->add(v);
		TElem elem(c, values);
		this->elems->add(elem);
		this->s++;
	}
}

vector<TValue> SortedMultiMap::search(TKey c) {
	vector<TValue> v;
	int pos;
	pos= this->elems->searchKey(c);
	if (pos == -1)
		return v;
	else {
		int currentNode = pos;
		/*
		int currentPos = 0;
		int currentNode = this->elems->head;
		while (currentNode != -1 && currentPos < pos - 1) {
			currentPos++;
			currentNode = this->elems->next[currentNode];
		}*/
		int currentPosVec = 0;
		int currentNodeVec = this->elems->elems[currentNode].second->getHead();
		while (currentNodeVec != -1) {
			v.push_back(currentNodeVec);
			currentPosVec++;
			currentNodeVec = this->elems->elems[currentNode].second->next[currentNodeVec];
		}
	}
	return v;
	//&& this->elems->elems[currentNode].second.next[currentNodeVec]!=-1
}

bool SortedMultiMap::remove(TKey c, TValue v) {
	int pos = this->elems->searchKey(c);
	if (pos == -1)
		return false;
	pos = this->elems->elems[pos].second->searchValue(v);
	if (pos == -1)
		return false;
	this->elems->remove(c, v);
	this->s--;
	return true;
}

int SortedMultiMap::size() const {
	return this->s;
}

bool SortedMultiMap::isEmpty() const {
	int s = this->s;
	if (s == 0)
		return true;
	return false;
}

SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this);
}

vector<TValue> SortedMultiMap::removeKey(TKey key) {

	vector<TValue> v;
	int pos = this->elems->searchKey(key);
	if (pos == -1)
		return v;
	v = this->search(key);
	//int reduceSize = this->elems->elems->second->size;
	TValue value=0;
	SLLAv *values = new SLLAv;
	TElem elem(key, values);
	this->elems->del(elem);
	this->s -= v.size();
	return v;
}

//constructor
SLLA::SLLA() {
	this->capacity = 10;
	this->firstEmpty = 0;
	this->head = -1;
	this->elems = new TElem[10];
	this->next = new int[10];
	for (int i = 0; i < this->capacity - 1; i++)
		this->next[i] = i + 1;
	this->next[this->capacity-1] = -1;
	this->size = 0;
}

//we need destructor to free memory

SLLA::~SLLA() {
	delete[] this->elems;
	delete[] this->next;
}

//FUNCTIONS:

int SLLA::searchKey(TKey key) {
	int current = this->head;
	while (current != -1) {
		if (this->elems[current].first == key) {
			return current;
		}
		current = this->next[current];
	}
	return -1;
}

void SLLA::del(TElem elem) {
	int nodC = this->head;
	int prevNode = -1;
	while (nodC != -1 && this->elems[nodC].first != elem.first) {
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
		this->size--;
	}
	else
		throw std::range_error("Element does not exist!");
}
void SLLA::insertPosition(TValue value, int pos) {
	if (pos < 0)
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
			this->elems[currentNode].second->add(value);
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
	while (currentNode != -1 && this->next[currentNode] != -1) {
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
	else {
		int newPos = this->firstEmpty;
		this->elems[newPos] = elem;
		this->firstEmpty = this->next[this->firstEmpty];
		this->next[newPos] = this->head;
		this->head = newPos;
		this->size++;
	}
}

void SLLA::remove(TKey key, TValue value) {
	int nodC = this->head;
	int prevNode = -1;
	while (nodC != -1 && this->elems[nodC].first != key) {
		prevNode = nodC;
		nodC = this->next[nodC];
	}
	if (nodC != -1 && this->elems[nodC].second->size < 2) {
		if (nodC = this->head)
			this->head = this->next[this->head];
		else
			this->next[prevNode] = this->next[nodC];
		this->next[nodC] = this->firstEmpty;
		this->firstEmpty = nodC;
		this->size--;
	}
	else if (nodC != -1 && this->elems[nodC].second->size >= 2) {
		this->elems[nodC].second->remove(value);
	}
	else
		throw std::range_error("Element does not exist!");
}


//constructor

SLLAv::SLLAv() {
	this->capacity = 10;
	this->firstEmpty = 0;
	this->head = -1;
	this->elems = new TValue[10];
	this->next = new int[10];
	for (int i = 0; i < this->capacity-1; i++)
		this->next[i] = i + 1;
	this->next[this->capacity-1] = -1;
	this->size = 0;
}

//we need destructor to free memory

SLLAv::~SLLAv() {
	//delete[] this->elems;
	//delete[] this->next;
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
	while (currentNode != -1 && this->next[currentNode] != -1) {
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
	else {
		int newPos = this->firstEmpty;
		this->elems[newPos] = elem;
		this->firstEmpty = this->next[this->firstEmpty];
		this->next[newPos] = this->head;
		this->head = newPos;
		this->size++;
	}
		
}

void SLLAv::remove(TValue elem) {
	int nodC = this->head;
	int prevNode = -1;
	while (nodC != -1 && this->elems[nodC] != elem) {
		prevNode = nodC;
		nodC = this->next[nodC];
	}
	if (nodC != -1) {
		if (nodC == this->head)
			this->head = this->next[this->head];
		else
			this->next[prevNode] = this->next[nodC];
		this->next[nodC] = this->firstEmpty;
		this->firstEmpty = nodC;
	}
	else
		throw std::range_error("Element does not exist!");
}