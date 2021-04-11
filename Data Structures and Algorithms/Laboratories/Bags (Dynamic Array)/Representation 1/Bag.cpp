#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
using namespace std;


Bag::Bag() {
	this->bag_lenght = 0;
	this->bag_capacity = 2;
	this->bag_array = new int[this->bag_capacity];
}


void Bag::resize() {
	//Complexity: Theta(n)
	int new_capacity = 2 * this->bag_capacity;
	int* new_array;
	int* old_array;

	old_array = bag_array;
	new_array = new int[new_capacity];

	for (int i = 0; i < this->bag_capacity; i++) {
		new_array[i] = old_array[i];
	}

	delete[] bag_array;
	bag_array = new_array;
	bag_capacity = new_capacity;
}

void Bag::add(TElem elem) {
	//Complexity: Theta(1) amortized
	if (this->bag_lenght == this->bag_capacity) {
		resize();
	}
	this->bag_array[this->bag_lenght] = elem;
	this->bag_lenght += 1;
}


bool Bag::remove(TElem elem) {
	//Complexity: O(n)
	for (int i = 0; i < this->bag_lenght; i++) {
		if (this->bag_array[i] == elem) {
			this->bag_array[i] = this->bag_array[this->bag_lenght - 1];
			this->bag_lenght -= 1;
			return true;
		}
	}
	return false;
}


bool Bag::search(TElem elem) const {
	//Complexity: O(n)
	for (int i = 0; i < this->bag_lenght; i++) {
		if (this->bag_array[i] == elem) {
			return true;
		}
	}
	return false;
}

int Bag::nrOccurrences(TElem elem) const {
	//Complexity: O(n)
	int no_of_occurrences = 0;
	for (int i = 0; i < this->bag_lenght; i++) {
		if (this->bag_array[i] == elem) {
			no_of_occurrences += 1;
		}
	}
	return no_of_occurrences;
}


int Bag::size() const {
	//Complexity: Theta(1)
	return this->bag_lenght;
}


bool Bag::isEmpty() const {
	//Complexity: Theta(1)
	return !this->bag_lenght;
}

BagIterator Bag::iterator() const {
	return BagIterator(*this);
}


Bag::~Bag() {
	if (this->bag_array != NULL) {
		delete[] this->bag_array;
	}
}
