#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;


BagIterator::BagIterator(const Bag& c): bag(c) {
	//Complexity: Theta(1)
	this->current = 0;
	this->positions_length = this->bag.size();
	this->positions = new int[this->positions_length];
	this->positions = this->bag.positions;
	this->items_length = this->bag.bag_length;
	this->items = new TElem[this->items_length];
	this->items = this->bag.bag_array;
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
	if (this->current >= this->positions_length) {
		return false;
	}
	return true;
}



TElem BagIterator::getCurrent() const {
	//Complexity: Theta(1)
	if (!this->valid()) {
		throw (std::exception());
	}
	return this->items[this->positions[this->current]];
}
