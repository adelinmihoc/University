#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
using namespace std;


Bag::Bag() {
	bag_capacity = 2;
	bag_lenght = 0;
	bag_size = 0;
	bag_array = new int[bag_capacity];
	minimumElement = NULL;
}


void Bag::resize() {
	//Complexity: Theta(n)
	int new_capacity = bag_capacity * 2;
	int* new_array;
	int* old_array;

	old_array = bag_array;
	new_array = new int[new_capacity];

	for (int i = 0; i < bag_capacity; i++) {
		new_array[i] = old_array[i];
	}

	delete[] bag_array;
	bag_array = new_array;
	bag_capacity = new_capacity;
}

void Bag::add(TElem elem) {
	//Complexity: O(n)
	if (bag_lenght == 0) {
		bag_array[0] = 1;
		minimumElement = elem;
		bag_lenght += 1;
		bag_size += 1;
		return;
	}
	int elementPosition = elem - minimumElement;
	if (elementPosition >= 0 && elementPosition < bag_lenght) {
		bag_array[elementPosition] += 1;
		bag_size += 1;
		return;
	}
	if (elementPosition < 0) {
		int displacement = 0 - elementPosition;
		int newSize = bag_lenght + displacement;
		while (newSize >= bag_capacity) {
			resize();
		}
		for (int i = newSize - 1; i >= displacement; i--) {
			bag_array[i] = bag_array[i - displacement];
		}
		for (int i = 1; i < displacement; i++) {
			bag_array[i] = 0;
		}
		bag_array[0] = 1;
		minimumElement = elem;
		bag_lenght = newSize;
		bag_size += 1;
		return;
	}
	if (elementPosition >= bag_lenght) {
		int newSize = elementPosition + 1;
		while (newSize >= bag_capacity) {
			resize();
		}
		for (int i = bag_lenght; i < newSize - 1; i++) {
			bag_array[i] = 0;
		}
		bag_array[elementPosition] = 1;
		bag_lenght = newSize;
		bag_size += 1;
		return;
	}
}


bool Bag::remove(TElem elem) {
	//Complexity: Theta(1)
	if (search(elem) == false) {
		return false;
	}
	bag_array[elem - minimumElement] -= 1;
	if (elem - minimumElement == bag_lenght - 1 && bag_array[elem - minimumElement] == 0) {
		bag_lenght -= 1;
	}
	bag_size -= 1;
	return true;
}


bool Bag::search(TElem elem) const {
	//Complexity: Theta(1)
	int elementPosition = elem - minimumElement;
	if (elementPosition < 0 || elementPosition >= bag_lenght) {
		return false;
	}
	return bag_array[elementPosition];
}

int Bag::nrOccurrences(TElem elem) const {
	//Complexity: Theta(1)
	if (elem - minimumElement < 0 || elem - minimumElement >= bag_lenght) {
		return 0;
	}
	return bag_array[elem - minimumElement];
}


int Bag::size() const {
	//Complexity: Theta(1)
	return bag_size;
}


bool Bag::isEmpty() const {
	//Complexity: Theta(1)
	return !bag_size;
}

BagIterator Bag::iterator() const {
	return BagIterator(*this);
}


Bag::~Bag() {
	if (bag_array != NULL) {
		delete[] bag_array;
	}
}
