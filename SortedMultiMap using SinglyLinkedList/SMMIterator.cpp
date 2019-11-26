#include "SMMIterator.h"
SMMIterator::SMMIterator(const SortedMultiMap& c) :smm(c) {
	if (this->smm.isEmpty())
		this->currentNode = -1;
	else {
		this->currentNode = this->smm.elems->head;
		this->currentNodeValues = this->smm.elems->elems->second->head;
	}
}
void SMMIterator::first() {
	this->currentNode = this->smm.elems->head;
	this->currentNodeValues = this->smm.elems->elems->second->head;
}
void SMMIterator::next() {

	/*while (this->currentNode != -1) {
		if (this->smm.elems->elems[currentNode].second->next[this->currentNodeValues] != -1)
			this->currentNodeValues = this->smm.elems->elems[currentNode].second->next[this->currentNodeValues];
		else {
			currentNode = this->smm.elems->next[currentNode];
			this->currentNodeValues = this->smm.elems->elems[currentNode].second->getHead();
		}
	}*/

	this->currentNode = -1;
	this->valid();
}

bool SMMIterator::valid() const {
	if (this->currentNode == -1)
		return false;
	return true;
}
TElem SMMIterator::getCurrent() const {
	return this->smm.elems->elems[currentNode];
}