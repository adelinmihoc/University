#include "Bag.h"
#include "ShortTest.h"
#include "ExtendedTest.h"
#include <iostream>

using namespace std;

int main() {

	testAll();
	cout << "Short tests over" << endl;
	testAllExtended();

	cout << "All test over" << endl;
	Bag b;
	b.add(4);
	b.add(1);
	b.add(6);
	b.add(4);
	b.add(7);
	b.add(2);
	b.add(1);
	b.add(1);
	b.add(1);
	b.add(9);
	b.add(-5);
	b.add(7);
	b.remove(6);
	b.remove(1);
	//b.showElems();
}