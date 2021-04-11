#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;


BagIterator::BagIterator(const Bag& c): bag(c){
	//Complexity: Theta(1) or n
	this->current = 0;
	this->size = bag.size();
	this->items = new TElem[this->size + 1];
	this->items = this->bag.bag_array;
}

void BagIterator::first() {
	//Complexity: Theta(1)
	this->current = 0;
}


void BagIterator::next() {
	//Complexity: Theta(1)
	if (!this->valid()) {
		throw std::exception();
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



TElem BagIterator::getCurrent() const {
	//Complexity: Theta(1)
	if (!this->valid()) {
		throw std::exception();
	}
	return this->items[this->current];
}
