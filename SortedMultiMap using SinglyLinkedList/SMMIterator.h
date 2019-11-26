#pragma once
#include <utility>
#include "SortedMultiMap.h"
//unidirectional iterator for a container

class SortedMultiMap;
class SLLA;
class SLLAv;
class SMMIterator {
	friend class SortedMultiMap;
	friend class SLLA;
	friend class SLLAv;
private:
	//contains a reference of the container it iterates over
	const SortedMultiMap& smm;
	
	/* representation specific for the iterator*/
	int currentNode;
	int currentNodeValues;
	//Constructor receives a reference of the container.
	//after creation the iterator will refer to the first element of the container, or it will be invalid if the container is empty
	SMMIterator(const SortedMultiMap& c);
public:

	//sets the iterator to the first element of the container
	void first();

	//moves the iterator to the next element
	//throws exception if the iterator is not valid
	void next();

	//checks if the iterator is valid
	bool valid() const;

	//returns the value f the current element from the iterator
	// throws excepion if the iterator is not valid
	TElem getCurrent() const;
};


