#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;


SortedMultiMap::SortedMultiMap(Relation r) {
    this->length = 0;
    this->capacity = 8192;
    this->hash_table = new TElem[this->capacity];
    for (int i = 0; i < this->capacity; i++) {
        hash_table[i] = NULL_TELEM;
    }
    this->relation = r;
}

void SortedMultiMap::add(TKey c, TValue v) {
    // Complexity:
    //      Best case: theta(1)
    //      Worst case: theta(n)
    //      Average case: O(n) ??
    if (this->length == this->capacity) {
        resize();
    }
    TElem element = make_pair(c, v);
    int i = 0;
    while (i < this->capacity) {
        if (hash_table[hash_function(element, i)] == NULL_TELEM) {
            hash_table[hash_function(element, i)] = element;
            this->length += 1;
            return;
        }
        i += 1;
    }
}

vector<TValue> SortedMultiMap::search(TKey c) const {
    // Complexity: theta(n)
    vector<TValue> result;
    for (int i = 0; i < this->capacity; i++) {
        if (this->hash_table[i].first == c) {
            result.push_back(this->hash_table[i].second);
        }
    }
	return result;
}

bool SortedMultiMap::remove(TKey c, TValue v) {
    // Complexity:
    //      Best case: theta(1)
    //      Worst case: theta(n)
    //      Average case: O(n) ??
    int i = 0;
    while (i < this->capacity) {
        if (hash_table[hash_function(make_pair(c, v), i)] == make_pair(c, v)) {
            hash_table[hash_function(make_pair(c, v), i)] = NULL_TELEM;
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

SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator{*this};
}

SortedMultiMap::~SortedMultiMap() {
	delete [] this->hash_table;
}

int SortedMultiMap::hash_function(TElem k, int i) {
    int random[2]{13, 77};
    return ((k.first * random[0] + k.second * random[1]) % this->capacity + int(0.5 * i + 0.5 * i * i)) % this->capacity;
}

void SortedMultiMap::resize() {
    int new_capacity = 2 * this->capacity;
    TElem* new_hash_table = new TElem[new_capacity];
    TElem* old_hash_table = this->hash_table;

    for (int i = 0; i < new_capacity; i++) {
        new_hash_table[i] = NULL_TELEM;
    }

    for (int i = 0; i < this->capacity; i++) {
        int j = 0;
        while (j < new_capacity) {
            if (new_hash_table[hash_function(old_hash_table[i], j)] == NULL_TELEM) {
                new_hash_table[hash_function(old_hash_table[i], j)] = old_hash_table[i];
                break;
            }
            j += 1;
        }
    }

    delete [] this->hash_table;
    this->capacity = new_capacity;
    this->hash_table = new_hash_table;

}

void SortedMultiMap::print_table() {
    for (int i = 0; i < this->capacity; i++) {
        std::cout << hash_table[i].first << " " << hash_table[i].second << "\n";
    }
    cout << hash_function(make_pair(3,2),2);
}
