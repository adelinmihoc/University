#include <iostream>
#include "ExtendedTest.h"
#include "ShortTest.h"
#include "Matrix.h"


int main() {
    testAll();
    testAllExtended();
    std::cout << "Test End" << std::endl;

    return 0;
}