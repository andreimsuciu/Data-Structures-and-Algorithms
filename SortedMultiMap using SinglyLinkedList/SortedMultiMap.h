#pragma once
#include <vector>
class SLLA;
class SLLAv;
typedef int TKey;
typedef int TValue;
typedef SLLAv *values;
#include <utility>

typedef std::pair<TKey, values> TElem;
using namespace std;
typedef bool(*Relation)(TKey, TKey);
#include "SMMIterator.h"
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
	//destructor
	~SLLA();

	//dynamic vector functions. they return bool to know if the function succeeds
	void add(TElem elem);
	void insertPosition(TValue value, int pos);
	void remove(TKey key, TValue value);
	int searchKey(TKey key);
	void del(TElem elem);
};

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

class SMMIterator;

class SortedMultiMap {
	friend class SMMIterator;
	friend class SLLA;
	friend class SLLAv;
private:
	
	/* representation of the SortedMultiMap */
	Relation rel;
	SLLA *elems;
	int s;

public:
	// constructor
	SortedMultiMap(Relation r);

	//adds a new key value pair to the sorted multi map
	void add(TKey c, TValue v);

	//returns the values belonging to a given key
	vector<TValue> search(TKey c) ;

	//removes a key value pair from the sorted multimap
	//returns true if the pair was removed (it was part of the multimap), false if nothing is removed
	bool remove(TKey c, TValue v);

	//returns the number of key-value pairs from the sorted multimap
	int size() const;

	//verifies if the sorted multi map is empty
	bool isEmpty() const;

	// returns an iterator for the sorted multimap. The iterator will returns the pairs as required by the relation (given to the constructor)	
	SMMIterator iterator() const;
	vector<TValue> removeKey(TKey key);
	// destructor
	~SortedMultiMap();

};