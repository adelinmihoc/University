#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <vector>
#include <exception>


SortedMultiMap::SortedMultiMap(Relation r) {
    // Complexity: theta(n) n - capacity
    this->relation = r;
    this->capacity = 8;
    this->length = 0;
    this->hash_table = new TElem[this->capacity];
    for (int i = 0; i < this->capacity; i++) {
        this->hash_table[i] = NULL_TELEM;
    }
}

void SortedMultiMap::add(TKey c, TValue v) {
    // Complexity:
    //      Best case: theta(1)
    //      Worst case: theta(n)
    //      Average case: O(n)
    if (this->length == this->capacity) {
        resize();
    }
	TElem element = std::make_pair(c, v);
	int i = 0;
	while (i < this->capacity) {
	    if (hash_table[hash_function_quadratic(c, i)] == NULL_TELEM) {
	        hash_table[hash_function_quadratic(c, i)] = element;
	        this->length += 1;
            return;
	    }
	    i += 1;
	}
}

vector<TValue> SortedMultiMap::search(TKey c) const {
    // Complexity: theta(n) n - capacity
	vector<TValue> result;
    int i = 0;
    while (i < this->capacity) {
        if (hash_table[hash_function_quadratic(c, i)].first == c) {
            result.push_back(hash_table[hash_function_quadratic(c, i)].second);
        }
        i += 1;
    }
	return result;
}

bool SortedMultiMap::remove(TKey c, TValue v) {
    // Complexity:
    //      Best case: theta(1)
    //      Worst case: theta(n)
    int i = 0;
    while (i < this->capacity) {
        if (hash_table[hash_function_quadratic(c, i)] == make_pair(c, v)) {
            hash_table[hash_function_quadratic(c, i)] = NULL_TELEM;
            this->length -= 1;
            return true;
        }
        i += 1;
    }
    return false;
}


int SortedMultiMap::size() const {
    // Complexity: theta(1)
	return this->length;
}

bool SortedMultiMap::isEmpty() const {
    // Complexity: theta(1)
	return !this->length;
}

SMMIterator SortedMultiMap::iterator(){
	return SMMIterator(*this);
}

SortedMultiMap::~SortedMultiMap() {
	delete [] this->hash_table;
}

int SortedMultiMap::hash_function(TKey key) const {
    // Complexity: theta(1)
    return key % this->capacity;
}

int SortedMultiMap::hash_function_quadratic(TKey key, int i) const {
    // Complexity: theta(1)
    return int(hash_function(key) + 0.5 * i + 0.5 * i * i) % this->capacity;
}

void SortedMultiMap::resize() {
    // Complexity: theta(n) n - capacity
    int new_capacity = 2 * this->capacity;
    TElem* new_hash_table = new TElem[new_capacity];
    TElem* old_hash_table = this->hash_table;

    for (int i = 0; i < new_capacity; i++) {
        new_hash_table[i] = NULL_TELEM;
    }

    for (int i = 0; i < this->capacity; i++) {
        int j = 0;
        while (j < new_capacity) {
            if (new_hash_table[hash_function_quadratic(old_hash_table[i].first, j)] == NULL_TELEM) {
                new_hash_table[hash_function_quadratic(old_hash_table[i].first, j)] = old_hash_table[i];
                break;
            }
            j += 1;
        }
    }

    delete [] this->hash_table;
    this->capacity = new_capacity;
    this->hash_table = new_hash_table;
}

