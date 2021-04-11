#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;


BagIterator::BagIterator(const Bag& c): bag(c) {
	//Complexity: Theta(1)
	this->current = 0;
	this->size = this->bag.size();
	this->lenght = this->bag.bag_length;
	this->items = new TElem[this->size];
	this->frequency = new int[this->size];
	this->items = this->bag.bag_array;
	this->frequency = this->bag.frequency_array;
}

void BagIterator::first() {
	//Complexity: Theta(1)
	this->current = 0;
}


void BagIterator::next() {
	//Complexity: Theta(1)
	if (!this->valid()) {
		throw (std::exception());
	}
	this->current += 1;
}


bool BagIterator::valid() const {
	//Complexity: Theta(1)
	if (this->current >= this->size) {
		return false;
	}
	return true;
}



TElem BagIterator::getCurrent() const{
	//Complexity: O(n)
	if (!this->valid()) {
		throw (std::exception());
	}
	int elements = 0;
	for (int i = 0; i < this->lenght; i++) {
		if (elements <= this->current) {
			elements += this->frequency[i];
		}
		if (elements > this->current) {
			return this->items[i];
		}
	}
}
