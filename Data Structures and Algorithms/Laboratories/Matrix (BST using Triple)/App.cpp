#include <iostream>
#include "Matrix.h"
#include "ExtendedTest.h"
#include "ShortTest.h"


int main() {
	testAll();
	testAllExtended();
	std::cout << "Test End" << "\n";
    return 0;
}