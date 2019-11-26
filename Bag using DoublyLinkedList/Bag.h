#pragma once

typedef int TElem;

typedef struct Node
{
	TElem elem;
	int frequency;
	struct Node *next;
	struct Node *prev;

} Node;

#include "BagIterator.h"

class BagIterator;

class Bag {

private:

	/*representation of Bag*/
	Node *head;
	Node *tail;
	int s;
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

	//in-lab functions
	void addOccurrences(int nr, TElem elem);
	//destructor
	~Bag();

};