#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;

BagIterator::BagIterator(const Bag& c) : bag(c) {
	//Complexity: O(n*m)
	iterator_current = 0;
	iterator_size = bag.size();
	iterator_elems = new TElem[iterator_size + 1];
	int pos = 0;
	for (int i = 0; i < bag.bag_lenght; i++) {
		int count = bag.bag_array[i];
		while (count--) {
			iterator_elems[pos++] = i + bag.minimumElement;
		}
	}
}

void BagIterator::first() {
	//Complexity: Theta(1)
	iterator_current = 0;
}

void BagIterator::next() {
	//Complexity: Theta(1)
	if (!valid())
		throw std::exception();
	iterator_current += 1;
}

bool BagIterator::valid() const {
	//Complexity: Theta(1)
	if (iterator_current >= iterator_size) {
		return false;
	}
	return true;
}

TElem BagIterator::getCurrent() const {
	//Complexity: Theta(1)
	if (!valid())
		throw std::exception();
	return iterator_elems[iterator_current];
}
