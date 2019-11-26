#pragma once
#include "BagIterator.h"
#include <climits>
#include <iostream>
typedef int TElem;
class BagIterator;

class Bag {
private:

	/*representation of Bag*/
	TElem *elems;
	int *next;
	int m;
	int s;
	int firstFree;
	int (*hash)(int, int);
	void resizeAndRehash(int newS);
	void changeFirstFree();
	friend class BagIterator;

public:

	//constructor

	Bag();
	//adds an element to the bag

	void add(TElem e);

	//removes one occurrence of an element from a bag

	//returns true if an element was removed, false otherwise (if e was not part of the bag)

	bool remove(TElem e);

	//checks if an element appearch is the bag

	bool search(TElem e) const;

	//returns the number of occurrences for an element in the bag

	int nrOccurrences(TElem e) const;

	//returns the number of elements from the bag
	int size() const;

	//returns an iterator for this bag

	BagIterator iterator() const;


	//checks if the bag is empty

	bool isEmpty() const;

	void print() {
		for (int i = 0; i < this->m; i++)
			std::cout << this->elems[i] << " ";
	}

	void addOccurrences(int nr, TElem elem);

	//destructor

	~Bag();

};
