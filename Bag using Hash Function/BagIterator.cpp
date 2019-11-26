#include "BagIterator.h"
#include "Bag.h"
#include <stdexcept>
#include <iostream>

BagIterator::BagIterator(const Bag & b) : bag(b)
{
	this->first();
}

void BagIterator::first()
{
	for (int i = 0; i < this->bag.m; i++)
		if (this->bag.elems[i] != INT_MIN) {
			this->currentElem = this->bag.elems[i];
			this->index = i;
			this->elems = 1;
			return;
		}
	this->index = -1;
	this->elems = 0;
}

void BagIterator::next()
{
	if(elems==this->bag.s+1)
		throw std::range_error("The Bag has finished iterating");
	else if(index==-1)
		throw std::range_error("The Bag has finished iterating");
	this->index++;
	for (int i = index; i < this->bag.m; i++) {
		if (this->bag.elems[i] != INT_MIN) {
			this->currentElem = this->bag.elems[i];
			this->index = i;
			elems++;
			return;
		}
	}
	elems++;
}

bool BagIterator::valid() const
{
	if (this->bag.s == 0) {
		return false;
	}
	if (elems== this->bag.s+1)
		return false;
	if (index == -1)
		return false;
	return true;
}

TElem BagIterator::getCurrent() const
{
	if(this->index==-1)
		throw std::range_error("The Bag is Empty");
	if (elems == this->bag.s + 1)
		throw std::range_error("The Bag is Empty");
	return this->currentElem;
}
