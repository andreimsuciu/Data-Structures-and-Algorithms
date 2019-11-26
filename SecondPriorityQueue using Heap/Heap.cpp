#include "Heap.h"
#include <exception>
#include <iostream>

Heap::Heap(const int & capacity)
{
	this->capacity = capacity;
	this->elements = new Element[this->capacity];
	this->length = 0;
}

Heap::Heap(const Heap & anotherHeap)
{
	this->capacity = anotherHeap.capacity;
	this->elements = anotherHeap.elements;
	this->length = anotherHeap.length;
}

Heap::Heap()
{
	this->elements = new Element[this->capacity];
	this->length = 0;
}

Element Heap::second(Relation r) const
{
	if (r(elements[1].second, elements[2].second) == true && r(elements[1].second, elements[3].second) == true)
	{
		return elements[1];
	}
	else if (r(elements[2].second, elements[1].second) == true && r(elements[2].second, elements[3].second) == true)
	{
		return elements[2];
	}
	else if (r(elements[3].second, elements[1].second) == true && r(elements[3].second, elements[2].second) == true)
	{
		return elements[3];
	}
}

void Heap::resize()
{
	Element* newElements = new Element[this->capacity * 2];

	for (int i = 0; i < this->capacity; i++)
		newElements[i] = this->elements[i];

	delete[] this->elements;

	this->elements = newElements;
	this->capacity = this->capacity * 2;
}

void Heap::bubbleUp(const int& p, Relation r)
{
	/*
	Complexity: log2 of n
	*/
	int position = p;
	Element element = this->elements[position];
	int parent = (position - 1) / 3;
	while (position > 0 && r(element.second, this->elements[parent].second) == true)
	{
		//move parent down
		this->elements[position] = this->elements[parent];
		position = parent;
		parent = (position - 1) / 3;
	}
	this->elements[position] = element;
}

void Heap::add(const Element& element, Relation r)
{
	if (this->length == this->capacity)
		this->resize();
	this->elements[this->length] = element;
	this->bubbleUp(this->length, r);
	this->length = this->length + 1;
}

void Heap::bubbleDown(const int& p, Relation r)
{
	/*
	Complexity: log2 of n
	*/
	int position = p;
	Element element = this->elements[p];
	while (position < this->length)
	{
		int maxChildPosition = -1;
		if ((position * 3) + 1 <= this->length)
		{
			//has a left child, assume it is the maximum
			maxChildPosition = (position * 3) + 1;
		}
		if ((position * 3) + 2 <= this->length && r(this->elements[(3 * position) + 2].second, this->elements[maxChildPosition].second) == true)
		{
			//it has two children and the right is greater
			maxChildPosition = (position * 3) + 2;
		}
		if ((position * 3) + 3 <= this->length && r(this->elements[(3 * position) + 3].second, this->elements[maxChildPosition].second) == true)
		{
			maxChildPosition = (position * 3) + 3;
		}
		if (maxChildPosition != -1 && r(this->elements[maxChildPosition].second, element.second) == true)
		{
			Element temporary = this->elements[position];
			this->elements[position] = this->elements[maxChildPosition];
			this->elements[maxChildPosition] = temporary;
			position = maxChildPosition;
		}
		else
		{
			position = this->length + 1;
		}
	}
}

Element Heap::remove(Relation r)
{
	//the root of the heap is removed
	
	if (this->length == 0)
		throw(std::exception("Empty heap!"));
	Element deletedElement = this->elements[0];
	this->elements[0] = this->elements[this->length - 1];
	this->length = this->length - 1;
	bubbleDown(0, r);
	return deletedElement;
}

int Heap::getLength() const
{
	return this->length;
}

Heap::~Heap()
{
	delete[] this->elements;
}