#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
using namespace std;


Bag::Bag() {
	this->bag_length = 0;
	this->bag_size = 0;
	this->bag_capacity = 2;
	this->bag_array = new TElem[bag_capacity];
	this->frequency_array = new int[bag_capacity];
}


void Bag::resize() {
	//Complexity: Theta(n)
	int new_capacity = 2 * this->bag_capacity;
	int* new_bag_array;
	int* new_frequency_array;
	int* old_bag_array;
	int* old_frequency_array;

	old_bag_array = this->bag_array;
	old_frequency_array = this->frequency_array;

	new_bag_array = new int[new_capacity];
	new_frequency_array = new int[new_capacity];

	for (int i = 0; i < this->bag_capacity; i++) {
		new_bag_array[i] = old_bag_array[i];
		new_frequency_array[i] = old_frequency_array[i];
	}

	delete[] this->bag_array;
	delete[] this->frequency_array;
	
	this->bag_array = new_bag_array;
	this->frequency_array = new_frequency_array;
	this->bag_capacity = new_capacity;

}


void Bag::add(TElem elem) {
	//Complexity: O(n)
	if (this->bag_capacity == this->bag_length) {
		resize();
	}
	for (int i = 0; i < this->bag_length; i++) {
		if (this->bag_array[i] == elem) {
			this->frequency_array[i] += 1;
			this->bag_size += 1;
			return;
		}
	}
	this->bag_array[this->bag_length] = elem;
	this->frequency_array[this->bag_length] = 1;

	this->bag_length += 1;
	this->bag_size += 1;
}


bool Bag::remove(TElem elem) {
	//Complexity: O(n)
	for (int i = 0; i < this->bag_length; i++) {
		if (this->bag_array[i] == elem) {
			if (this->frequency_array[i] == 1) {
				this->bag_array[i] = this->bag_array[this->bag_length - 1];
				this->frequency_array[i] = this->frequency_array[this->bag_length - 1];
				this->bag_size -= 1;
				this->bag_length -= 1;
				return true;
			}
			else {
				this->frequency_array[i] -= 1;
				this->bag_size -= 1;
				return true;
			}
		}
	}
	return false; 
}


bool Bag::search(TElem elem) const {
	//Complexity: O(n)
	for (int i = 0; i < this->bag_length; i++) {
		if (this->bag_array[i] == elem) {
			return true;
		}
	}
	return false; 
}

int Bag::nrOccurrences(TElem elem) const {
	//Complexity: O(n)
	for (int i = 0; i < this->bag_length; i++) {
		if (this->bag_array[i] == elem) {
			return this->frequency_array[i];
		}
	}
	return 0;
}


int Bag::size() const {
	//Complexity: Theta(1)
	return this->bag_size;
}


bool Bag::isEmpty() const {
	//Complexity: Theta(1)
	return !this->bag_size;
}

BagIterator Bag::iterator() const {
	return BagIterator(*this);
}


Bag::~Bag() {
	if (this->bag_array != NULL) {
		delete[] this->bag_array;
	}
	if (this->frequency_array != NULL) {
		delete[] this->frequency_array;
	}
}

