#include "Bag.h"
#include <stdexcept>

Bag::Bag() {
	this->head = nullptr;
	this->tail = nullptr;
	this->s = 0;
}

Bag::~Bag() {
}

void Bag::add(TElem elem) {
	//if bag is empty, we need to create the first node
	if (this->head == nullptr) {
		
		Node *newNode;
		newNode = new Node;
		newNode->prev = nullptr;
		newNode->next = nullptr;
		newNode->elem = elem;
		newNode->frequency = 1;

		this->s = 1;
		this->head = newNode;
		this->tail = newNode;
		return;
	}

	//if bag is not empty

	//1.we search to see if we already have the elem in the list to update freq.
	Node *currentNode = this->head;
	while (currentNode != nullptr) {
		if (currentNode->elem == elem)
		{
			currentNode->frequency += 1;
			this->s += 1;
			return;
		}
		currentNode = currentNode->next;
	}

	//2.if elem is not in list, we add a new node to its tail.
	Node *newNode;
	newNode = new Node;
	newNode->prev = this->tail;
	newNode->next = nullptr;
	newNode->elem = elem;
	newNode->frequency = 1;

	this->tail->next = newNode;
	this->tail = newNode;
	this->s += 1;
	return;
}

bool Bag::remove(TElem elem){
	Node *currentNode = this->head;
	while (currentNode != nullptr) {
		//the element is in the bag
		if (currentNode->elem == elem)
		{
			//if the element is in the bag more than once, we just update the freq
			if (currentNode->frequency > 1) {
				currentNode->frequency -= 1;
				this->s-= 1;
				return true;
			}
			//if elem is in the bag just once, we need to update the nodes
			if (currentNode->frequency == 1) {
				Node *prevNode = currentNode->prev, *nextNode = currentNode->next;

				//if there is only one node, we need to empty bag
				if (prevNode == nullptr && nextNode == nullptr) {
					this->head = nullptr;
					this->tail = nullptr;
					this->s -=1;
					return true;
				}
				//if the node is the head we need to make next element the head
				if (prevNode == nullptr) {
					nextNode->prev = nullptr;
					this->head = nextNode;
					this->s-= 1;
					return true;
				}
				//if the node is the tail we need to make prev element the tail
				if (nextNode == nullptr) {
					prevNode->next = nullptr;
					this->tail = prevNode;
					this->s-= 1;
					return true;
				}
				//if the node is inbetween
				nextNode->prev = prevNode;
				prevNode->next = nextNode;
				this->s -=1;
				return true;
			}
		}
		currentNode = currentNode->next;
	}
	return false;
}

bool Bag::search(TElem elem) const{
	Node *currentNode = this->head;
	while (currentNode != nullptr) {
		if (currentNode->elem == elem)
			return true;
		currentNode = currentNode->next;
	}
	return false;
}

int Bag::nrOccurrences(TElem elem) const {
	Node *currentNode = this->head;
	while (currentNode != nullptr) {
		if (currentNode->elem == elem)
			return currentNode->frequency;
		currentNode = currentNode->next;
	}
	return 0;
}

int Bag::size() const {
	return this->s;
}

bool Bag::isEmpty() const {
	if (this->s == 0)
		return true;
	return false;
}

BagIterator Bag::iterator() const{
	return BagIterator(*this);
}

void Bag::addOccurrences(int nr, TElem elem) {
	if (nr < 0) {
		throw std::range_error("The Number cannot be negative!");
	}
	bool found = false;
	Node *currentNode = this->head;
	while (currentNode != nullptr) {
		if (currentNode->elem == elem) {
			currentNode->frequency += nr;
			this->s += nr;
			found = true;
		}
		currentNode = currentNode->next;
	}
	if (found == false) {
		this->add(elem);
		nr--;
		currentNode = this->tail;
		if (currentNode->elem == elem) {
			currentNode->frequency += nr;
			this->s += nr;
		}

	}
}