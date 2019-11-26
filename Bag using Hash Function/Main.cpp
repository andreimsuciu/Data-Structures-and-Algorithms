#include "Bag.h"
#include "BagIterator.h"
#include <crtdbg.h>
#include <windows.h>
#include "ShortTest.h"
#include "ExtendedTest.h"
#include <assert.h>
#include <exception>
#include <iostream>

int main() {
	
	//in-lab test
	Bag b;
	b.add(21);
	b.addOccurrences(5,5);
	b.add(21);
	try {
		b.addOccurrences(-5, 5);
		assert(false);
	}
	catch (std::exception&) {
		assert(true);
	}
	assert(b.size() == 7);
	assert(b.search(5) == true);
	assert(b.search(21) == true);
	assert(b.nrOccurrences(5) == 5);
	assert(b.nrOccurrences(21) == 2);
	
	Bag b2;
	b2.add(21);
	b2.addOccurrences(100, 5);
	b2.add(21);
	try {
		b2.addOccurrences(-5, 5);
		assert(false);
	}
	catch (std::exception&) {
		assert(true);
	}
	assert(b2.size() == 102);
	assert(b2.search(5) == true);
	assert(b2.search(21) == true);
	assert(b2.nrOccurrences(5) == 100);
	assert(b2.nrOccurrences(21) == 2);
	
	testAll();
	testAllExtended();
	system("pause");
	_CrtDumpMemoryLeaks();

	return 0;
}