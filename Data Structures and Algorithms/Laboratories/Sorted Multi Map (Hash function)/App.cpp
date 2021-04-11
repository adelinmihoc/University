#include <iostream>

#include "ShortTest.h"
#include "ExtendedTest.h"
#include "SortedMultiMap.h"
#include "SMMIterator.h"

bool rel(TKey key1, TKey key2) {
    return key1 >= key2;
}

int main() {
    SortedMultiMap smm{rel};
    smm.add(1,2);
    smm.add(2,2);
    smm.add(3,2);
    smm.add(4,2);
    smm.add(5,2);
    smm.add(6,2);
    smm.add(7,2);
    smm.add(8,2);
    smm.add(9,2);
    smm.add(10,2);
    smm.add(11,2);
    smm.add(12,2);
    smm.add(13,2);
    smm.add(14,2);
    smm.add(15,2);
    smm.add(16,2);
    auto it = smm.iterator();
    testAll();
	testAllExtended();
    std::cout << "Finished SMM Tests!" << std::endl;

    return 0;
}
