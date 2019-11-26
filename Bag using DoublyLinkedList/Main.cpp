#include "BagIterator.h"
#include "Bag.h"
#include "ShortTest.h"
#include "ExtendedTest.h"
#include <crtdbg.h>
#include <windows.h>
#include <iostream>


int main() {
	std::cout << "Short test is running...";
	testAll();
	std::cout<<"Short Test works!\n";
	std::cout << "Extended test is running...\n";
	testAllExtended();
	std::cout << "Extended test works!\n";
	system("pause");
	_CrtDumpMemoryLeaks();

	return 0;
}