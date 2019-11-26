#include "Bag.h"
#include <stdexcept>

int hash_fct(int key, int m) {
	int res = key % m;
	if (res < 0) {
		res = -res;
	}
	return res;
}

Bag::Bag() {
	this->s = 0;
	this->m = 16;
	this->elems = new TElem[16];
	this->next = new int[16];
	this->hash = &hash_fct;
	this->firstFree = 0;
	for (int i = 0; i <= m-1; i++) {
		this->next[i] = -1;
		this->elems[i] = INT_MIN;
	}
}

bool Bag::isEmpty() const
{
	if (this->s <= 0)
		return true;
	return false;
}

void Bag::addOccurrences(int nr, TElem elem)
{
	/*
	Adds nr occurrences of elem in the Bag
	@throws exception if nr is negative
	Complexity: Theta(nr)
	*/
	if(nr<0)
		throw std::range_error("Number must be greater than 0");

	if (this->s + nr >= this->m) {
		this->resizeAndRehash(this->s+nr);
	}
	int pos = this->hash(elem, this->m);

	if (this->elems[pos] == INT_MIN) {
		this->elems[pos] = elem;
		this->next[pos] = -1;
		this->s++;
		if (pos == this->firstFree)
			this->changeFirstFree();
		nr--;
	}

	while (nr != 0) {
		while (this->next[pos] != -1)
			pos = this->next[pos];
		this->elems[this->firstFree] = elem;
		this->next[this->firstFree] = -1;
		this->next[pos] = this->firstFree;
		this->changeFirstFree();
		this->s++;
		nr--;
	}
}

Bag::~Bag() {
	delete[] this->elems;
	delete[] this->next;
}

void Bag::resizeAndRehash(int newS) {
	int old_m = this->m, pos, current;
	this->firstFree = 0;
	while(newS>=this->m)
		this->m = this->m * 2;

	TElem *newElems = new TElem[this->m];
	int *newNext = new int[this->m];

	for (int i = 0; i <this->m; i++)
		newNext[i] = -1;

	for (int i = 0; i < this->m; i++) {
		newElems[i] = INT_MIN;
	}

	for (int i = 0; i < old_m; i++) {
		current = this->elems[i];
		pos = this->hash(current, this->m);
		if (newElems[pos] == INT_MIN) {
			newElems[pos] = current;
			newNext[pos] = -1;
			if (pos == this->firstFree) {

				//change first free for new
				this->firstFree++;
				while (this->firstFree < this->m && newElems[this->firstFree] != INT_MIN)
					this->firstFree++;
			}
		}
		else {
			while (newNext[pos] != -1)
				pos = newNext[pos];
			newElems[this->firstFree]=current;
			newNext[this->firstFree] = -1;
			newNext[pos] = this->firstFree;
			//change first free for new
			this->firstFree++;
			while (this->firstFree < this->m && newElems[this->firstFree] != INT_MIN)
				this->firstFree++;
		}
	}
	delete[] this->elems;
	delete[] this->next;
	this->elems = newElems;
	this->next = newNext;
}

void Bag::changeFirstFree()
{
	this->firstFree++;
	while (this->firstFree < this->m && this->elems[this->firstFree] != INT_MIN)
		this->firstFree++;
}

void Bag::add(TElem e) {
	//Theta(1), Theta(n)
	/*
	if (this->s == this->m) {
		this->resizeAndRehash();
	}
	int pos = this->hash(e, this->m);
	while (this->elems[pos] != INT_MIN) {
		pos = this->next[pos];
	}
	this->elems[pos] = e;
	this->s++;
	*/
	int pos = this->hash(e, this->m);
	if (this->elems[pos] == INT_MIN) {
		this->elems[pos] = e;
		this->next[pos] = -1;
		this->s++;
		if (pos == this->firstFree)
			this->changeFirstFree();
	}
	else {
		if (this->s == this->m) {
			this->resizeAndRehash(this->s);
		}
		int current = this->hash(e, this->m);
		while (this->next[current] != -1)
			current = this->next[current];
		this->elems[this->firstFree] = e;
		this->next[this->firstFree] = -1;
		this->next[current] = this->firstFree;
		this->changeFirstFree();
		this->s++;
	}
}
bool Bag::remove(TElem e)
{
	int pos = this->hash(e, this->m);
	int prev_pos = -1;
	int idx = 0;
	while (idx < this->m && prev_pos == -1) {
		if (this->next[idx] == pos)
			prev_pos = idx;
		else
			idx++;
	}
	while (pos != -1 && this->elems[pos] != e) {
		prev_pos = pos;
		pos = this->next[pos];
	}
	if (pos == -1)
		return false;
	else {
		bool over = false;
		do {
			int p = this->next[pos];
			int pp = pos;
			while (p != -1 && this->hash(this->elems[p], this->m) != pos) {
				pp = p;
				p = this->next[p];
			}
			if (p == -1)
				over = true;
			else {
				this->elems[pos] = this->elems[p];
				prev_pos = pp;
				pos = p;
			}
		} while (!over);
		if (prev_pos != -1)
			this->next[prev_pos] = this->next[pos];
		this->elems[pos] = INT_MIN;
		this->next[pos] = -1;
		if (this->firstFree > pos)
			this->firstFree = pos;
		this->s--;
	}
	return true;
}

bool Bag::search(TElem e) const
{
	int pos = this->hash(e, this->m);
	while (pos != -1 && this->elems[pos] != e)
		pos = this->next[pos];
	if (pos == -1)
		return false;
	else
		return true;
}

int Bag::nrOccurrences(TElem e) const
{
	int occurances=0;
	for (int i = 0; i < this->m; i++) {
		int currentElem = this->elems[i];
		if (currentElem == e)
			occurances++;
	}
	return occurances;
}

int Bag::size() const
{
	return this->s;
}

BagIterator Bag::iterator() const
{
	return BagIterator(*this);
}
