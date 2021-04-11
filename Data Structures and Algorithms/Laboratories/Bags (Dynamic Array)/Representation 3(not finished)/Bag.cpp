#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
using namespace std;


Bag::Bag() {
	this->bag_length = 0;
	this->bag_capacity = 2;
	this->position_length = 0;
	this->position_capacity = 2;
	this->bag_array = new TElem[this->bag_capacity];
	this->positions = new TElem[this->bag_capacity];
}


void Bag::showElems() {
	/*for (int i = 0; i < this->bag_length; i++) {
		std::cout << "|" << this->bag_array[i] << "|";
	}
	std::cout << "\n";*/
	for (int i = 0; i < this->position_length; i++) {
		std::cout << "|" << this->bag_array[this->positions[i]] << "|";
	}
}


void Bag::resize() {
	//Complexity: Theta(n)
	int new_capacity = 2 * this->bag_capacity;
	TElem* new_array;
	TElem* old_array;

	old_array = this->bag_array;
	new_array = new TElem[new_capacity];

	for (int i = 0; i < this->bag_capacity; i++) {
		new_array[i] = old_array[i];
	}

	delete[] this->bag_array;
	this->bag_array = new_array;
	this->bag_capacity = new_capacity;
}


void Bag::resize_positions() {
	//Complexity: Theta(n)
	int new_capacity = 2 * this->position_capacity;
	int* new_array;
	int* old_array;

	old_array = this->positions;
	new_array = new int[new_capacity];

	for (int i = 0; i < this->position_capacity; i++) {
		new_array[i] = old_array[i];
	}

	delete[] this->positions;

	this->positions = new_array;
	this->position_capacity = new_capacity;
}


void Bag::add(TElem elem) {
	//Complexity: O(n)
	if (this->search(elem)) { // if elem already exists
		for (int i = 0; i < this->bag_length; i++) { // search for its position to add it in positions
			if (this->bag_array[i] == elem) {
				if (this->position_capacity == this->position_length) { // resize of positions needed
					resize_positions();
				}
				this->positions[this->position_length] = i;
				this->position_length += 1;
			}
		}
	}
	else { // new elem
		if (this->bag_capacity == this->bag_length) { // resize of bag_array needed
			resize();
		}
		this->bag_array[this->bag_length] = elem; // first add in bag_array
		this->bag_length += 1;
		//second add its position in the positions
		if (this->position_capacity == this->position_length) { // resize of positions needed
			resize_positions();
		}
		this->positions[this->position_length] = this->bag_length - 1; // new elem, already know its position
		this->position_length += 1;
	}
}


bool Bag::remove(TElem elem) {
	//Complexity: O(n + m)
	if (!this->search(elem)) { // inexistent elem
		return false;
	}
	int position = -1;
	if (this->nrOccurrences(elem) == 1) { // just one of a kind
		for (int i = 0; i < this->bag_length; i++) { // search for elem's position
			if (this->bag_array[i] == elem) {
				position = i;
			}
		}
		this->positions[position] = this->positions[this->position_length - 1]; // put last position in the position of the removed element
		for (int i = 0; i < this->position_length; i++) { // update all positions of the moved element (moved in the next step)
			if (this->positions[i] == this->bag_length - 1) {
				this->positions[i] = position;
			}
		}
		this->bag_array[position] = this->bag_array[this->bag_length - 1]; // put last elem in the removed elem's place
		this->bag_length -= 1;
		this->position_length -= 1;
		return true;
	}
	// if there are more occurrences
	for (int i = 0; i < this->bag_length; i++) { // search for elem's position
		if (this->bag_array[i] == elem) {
			position = i;
		}
	} 
	for (int i = 0; i < this->position_length; i++) {
		if (this->positions[i] == position) {
			this->positions[i] = this->positions[this->position_length - 1]; // put last position in the position of the removed element
			this->position_length -= 1;
			return true;
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
	//Complexity: O(n + m)
	if (!search(elem)) { // inexistent elem
		return 0;
	}
	int position = -1;
	int no_of_occurrences = 0;
	for (int i = 0; i < this->bag_length; i++) { // search for elem's position
		if (this->bag_array[i] == elem) {
			position = i;
		}
	}
	for (int i = 0; i < this->position_length; i++) { // search for position in positions
		if (this->positions[i] == position) {
			no_of_occurrences += 1;
		}
	}
	return no_of_occurrences;
}


int Bag::size() const {
	//Complexity: Theta(1)
	return this->position_length;
}


bool Bag::isEmpty() const {
	//Complexity: Theta(1)
	return !this->position_length;
}

BagIterator Bag::iterator() const {
	return BagIterator(*this);
}


Bag::~Bag() {
	if (this->bag_array != NULL) {
		delete[] this->bag_array;
	}
	if (this->positions != NULL) {
		delete[] this->positions;
	}
}

