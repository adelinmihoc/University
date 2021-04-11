#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <algorithm>


SMMIterator::SMMIterator(SortedMultiMap& d) : map(d) {
    // Complexity: theta(n*log(n))
	for (int i = 0; i < d.capacity; i++) {
	    if (d.hash_table[i] != NULL_TELEM) {
	        this->sorted_vector.push_back(d.hash_table[i]);
	    }
	}
	this->capacity = sorted_vector.size();
    /*{
        sort(sorted_vector.begin(), sorted_vector.end(), [this](TElem a, TElem b) {return this->relation(a, b);});
    }*/
    this->mergeSort(this->sorted_vector, 0, this->sorted_vector.size() - 1);
	this->current = 0;
}

void SMMIterator::first() {
    // Complexity: theta(1)
    this->current = 0;
}

void SMMIterator::next() {
    // Complexity: theta(1)
    if (!valid()) {
        throw std::exception();
    }
	this->current += 1;
}

bool SMMIterator::valid() const {
    // Complexity: theta(1)
    return this->current < this->capacity;
}

TElem SMMIterator::getCurrent() const {
    // Complexity: theta(1)
	if (!valid()) {
	    throw std::exception();
	}ch
	return sorted_vector[this->current];
}

TElem SMMIterator::remove() {
    // Complexity: O(n)
    TElem elem = this->getCurrent();
    this->sorted_vector.erase(this->sorted_vector.begin() + this->current);
    this->map.remove(elem.first, elem.second);
    this->current += 1;

    return elem;
}


