#include "BagIterator.h"
#include "Bag.h"
#include <stdexcept>

TElem BagIterator::getCurrent() const {
	if (this->currentNode == nullptr)
		throw std::range_error("The Bag is Empty");
	return this->currentNode->elem;
}

void BagIterator::next() {
	if (this->currentNode == nullptr)
		throw std::range_error("The Bag has finished iterating");
	//first, check if we are at the same pair
	if (this->currentNode->frequency > this->currentFrequency) {
		this->currentFrequency += 1;
		return;
	}
	//if not, move to next node
	this->currentNode = this->currentNode->next;
	this->currentFrequency = 1;
}

bool BagIterator::valid() const{
	if (this->currentNode == nullptr)
		return false;
	else
		return true;
}

void BagIterator::first() {
	this->currentNode = this->bag.head;
	this->currentFrequency = 1;
}

BagIterator::BagIterator(const Bag& b) : bag(b) {
	this->currentNode = this->bag.head;
	this->currentFrequency = 1;
}