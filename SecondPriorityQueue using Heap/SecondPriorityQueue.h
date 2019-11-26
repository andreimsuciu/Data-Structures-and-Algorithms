#pragma once
#include "Heap.h"

class SecondPriorityQueue 
{
private:
	Relation r;
	Heap hp{};
public:
	//implicit constructor
	SecondPriorityQueue(Relation r);
	//adds an element with priority to the queue
	void push(TElem e, TPriority p);
	//returns the element with the highest priority with respect to the order relation
	//throws exception if the queue is empty
	Element top()  const;
	//removes and returns the element with the highest priority
	//throws exception if the queue is empty
	Element pop();
	//checks if the queue is empty
	bool atMostOne() const;
	//destructor
	~SecondPriorityQueue();
};