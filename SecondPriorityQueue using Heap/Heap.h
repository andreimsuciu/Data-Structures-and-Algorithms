#pragma once
#include <utility>
typedef int TElem;
typedef int TPriority;
typedef std::pair<TElem, TPriority> Element;
typedef bool(*Relation)(TPriority p1, TPriority p2);

class Heap 
{
private:
	int capacity = 10;
	int length;
	Element* elements;
public:
	Heap(const int& capacity);
	Heap(const Heap& anotherHeap);
	Heap();
	Element second(Relation relation) const;
	void resize();
	void bubbleUp(const int& position, Relation relation);
	void add(const Element& element, Relation relation);
	void bubbleDown(const int& position, Relation relation);
	Element remove(Relation relation);
	int getLength() const;
	~Heap();
};