#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <algorithm>
#include <iostream>

SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d){
	this->capacity = -1;
	this->sorted_array = new TElem[d.length + 1];

	for (int i = 0; i < d.capacity; i++) {
	    if (d.hash_table[i] != NULL_TELEM) {
	        sorted_array[++capacity] = d.hash_table[i];
	    }
	}

    std::sort(sorted_array, sorted_array + capacity, [](TElem a, TElem b) {return a.first < b.first;});

	this->current = 0;
}

void SMMIterator::first(){
    this->current = 0;
}

void SMMIterator::next(){
    if (!this->valid()) {
        throw std::exception();
    }
    this->current += 1;
}

bool SMMIterator::valid() const {
    if (capacity < 0) {
        return false;
    }
    return this->current <= this->capacity;
}

TElem SMMIterator::getCurrent() const{
    if (!this->valid()) {
        throw std::exception();
    }
	return this->sorted_array[this->current];
}
