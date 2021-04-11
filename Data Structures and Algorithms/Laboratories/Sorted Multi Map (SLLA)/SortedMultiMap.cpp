#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;


SortedMultiMap::SortedMultiMap(Relation r) {
    // Complexity: theta(n) n - initial capacity
    this->relation = r;
    this->capacity = 10;
    this->elements = new std::pair<TKey, SLLA_values>[this->capacity];
    this->next = new int[this->capacity];
    this->head = -1;
    for (int i = 0; i < this->capacity; i++) {
        this->next[i] = i + 1;
    }
    this->next[this->capacity - 1] = -1;
    this->first_empty = 0;
    this->_size = 0;
    this->number_of_elements = 0;
}


void SortedMultiMap::resize() {
    // Complexity: theta(n)
    int new_capacity = 2 * this->capacity;
    auto* new_elements = new std::pair<TKey, SLLA_values>[new_capacity];
    int* new_next = new int[new_capacity];
    for (int i = 0; i < this->capacity; i++) {
        new_elements[i] = this->elements[i];
        new_next[i] = this->next[i];
    }
    for (int i = this->capacity; i < new_capacity - 1; i++) {
        new_next[i] = i + 1;
    }
    new_next[new_capacity - 1] = -1;
    delete [] this->elements;
    delete [] this->next;
    this->elements = new_elements;
    this->next = new_next;
    this->first_empty = this->capacity;
    this->capacity = new_capacity;
}


vector<TValue> SortedMultiMap::search(TKey c) const {
    // Complexity: O(n + m) n - size of keys; m - size of values
    int current_node = this->head;
    while (current_node != -1 && this->elements[current_node].first != c) {
        current_node = this->next[current_node];
    }
    if (current_node != -1) {
        return this->elements[current_node].second.get_all();
    }
    return vector<TValue>();
}


void SortedMultiMap::add(TKey c, TValue v) {
	// Complexity: O(n + m)
	if (!search(c).empty()) {
	    // key already exists
	    // add just a value
	    int current_node = this->head;
	    int current_position = 0;
	    while (current_node != -1 && this->elements[current_node].first != c) {
	        current_node = this->next[current_node];
	        current_position += 1;
	    }
	    if (current_node != -1) {
	        this->elements[current_node].second.add(v);
            this->number_of_elements += 1;
        }
	} else {
	    SLLA_values new_slla_values = SLLA_values();
	    new_slla_values.add(v);
	    pair<int, SLLA_values> element = std::make_pair(c, new_slla_values);
	    if (this->_size == 0) { // first element ever
            this->insert_at_position(element, 0);
	    } else {
            int current_position = 0;
            int current_node = this->head;
            while (current_node != -1 && current_position < this->_size && this->relation(this->elements[current_node].first, element.first)) {
                current_position += 1;
                current_node = this->next[current_node];
            }
            if (current_node != -1) {
                this->insert_at_position(element, current_position);
            } else {
                this->insert_at_position(element, this->first_empty);
            }
	    }
	}
}


bool SortedMultiMap::remove(TKey c, TValue v) {
    // Complexity: O(n * m)
    if (this->search(c).empty()) {
        return false;
    }
    // removing values
    int current_node = this->head;
    int previous_node = -1;
    while (current_node != -1 && this->elements[current_node].first != c) {
        previous_node = current_node;
        current_node = this->next[current_node];
    }
    if (current_node != -1) {
        if (!this->elements[current_node].second.search(v)) {
            return false;
        }
        if (this->elements[current_node].second.remove(v)) {
            this->number_of_elements -= 1;
        } else {
            return false;
        }
    }

    // if the key remained empty
    if (this->search(c).empty()) {
        if (current_node == this->head) {
            this->head = this->next[this->head];
            this->next[current_node] = this->first_empty;
            this->first_empty = current_node;
        } else {
            this->next[previous_node] = this->next[current_node];
            this->next[current_node] = this->first_empty;
            this->first_empty = current_node;
        }
        this->_size -= 1;
    }
    return true;
}


int SortedMultiMap::size() const {
    // Complexity: theta(1)
	return this->number_of_elements;
}


bool SortedMultiMap::isEmpty() const {
    // Complexity: theta(1)
    return !this->number_of_elements;
}


SMMIterator SortedMultiMap::iterator() const {
    // Complexity: theta(1)
	return SMMIterator(*this);
}


SortedMultiMap::~SortedMultiMap() {
    // Complexity: theta(1)
    delete [] this->elements;
    delete [] this->next;
}

/*std::vector<std::pair<TKey, SLLA_values>> SortedMultiMap::get_all() {
    // just for private tests
    std::vector<std::pair<TKey, SLLA_values> > result;
    int current_node = this->head;
    int count = 0;
    while (current_node != -1 && count < this->_size) {
        result.push_back(this->elements[current_node]);
        current_node = this->next[current_node];
        count++;
    }
    return result;
}*/

void SortedMultiMap::insert_at_position(const pair<int, SLLA_values>& element, int pos) {
    // Complexity: O(n)
    bool ok = false;
    if (pos == first_empty) {
        ok = true;
    }

    if (this->first_empty == -1) {
        this->resize();
    }
    if (ok == true) {
        pos = first_empty;
    }
    // create an element
    /*SLLA_values new_slla_values = SLLA_values();
    new_slla_values.add(v);
    pair<int, SLLA_values> element = std::make_pair(c, new_slla_values);*/

    if (pos == 0) {
        int new_position = this->first_empty;
        this->elements[new_position] = element;
        this->first_empty = this->next[this->first_empty];
        this->next[new_position] = this->head;
        this->head = new_position;
        this->_size += 1;
        this->number_of_elements += 1;
    } else {
        int current_position = 0;
        int current_node = this->head;
        while(current_node != -1 && current_position < pos - 1) {
            current_position += 1;
            current_node = this->next[current_node];
        }
        if (current_node != -1) {
            int new_element = this->first_empty;
            this->first_empty = this->next[this->first_empty];
            this->elements[new_element] = element;
            this->next[new_element] = this->next[current_node];
            this->next[current_node] = new_element;
            this->_size += 1;
            this->number_of_elements += 1;
        } else {
            throw std::exception();
        }
    }
}

std::vector<TKey> SortedMultiMap::key_set() const {
    // Complexity: theta(n)
    std::vector<TKey> result;
    int current_node = this->head;
    int count = 0;
    while (current_node != -1 && count < this->_size) {
        result.push_back(this->elements[current_node].first);
        current_node = this->next[current_node];
        count++;
    }
    return result;
}


