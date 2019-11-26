#include "SecondPriorityQueue.h"
#include <exception>

SecondPriorityQueue::SecondPriorityQueue(Relation r)
{
	this->r = r;
}

void SecondPriorityQueue::push(TElem e, TPriority p)
{
	//Complexity: O(log2 of n)
	Element newElement;
	newElement.first = e;
	newElement.second = p;
	hp.add(newElement, r);
}

Element SecondPriorityQueue::top() const
{
	//Complexity: O(1)
	if (this->atMostOne() == true)
		throw std::exception();
	return hp.second(r);
}

Element SecondPriorityQueue::pop()
{
	//Complexity: O(log2 of n)
	if (this->atMostOne() == true)
		throw std::exception();
	Element initialRoot = hp.remove(this->r);
	Element secondRoot = hp.remove(this->r);
	hp.add(initialRoot, this->r);
	return secondRoot;
}

bool SecondPriorityQueue::atMostOne() const
{
	//Complexity:Theta(1)

	return hp.getLength() <= 1;
}

SecondPriorityQueue::~SecondPriorityQueue()
{
}

