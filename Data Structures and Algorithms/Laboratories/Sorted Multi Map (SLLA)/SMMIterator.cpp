#include "SMMIterator.h"
#include "SortedMultiMap.h"

SMMIterator::SMMIterator(const SortedMultiMap& d) : map(d){
    // Complexity: theta(1)
    key_node = map.head;
    value_node = map.elements[key_node].second.head;
    key_count = 0;
    value_count = 0;
}

void SMMIterator::first(){
    // Complexity: theta(1)
    key_node = map.head;
    value_node = map.elements[key_node].second.head;
    key_count = 0;
    value_count = 0;
}

void SMMIterator::next(){
    // Complexity: theta(1)
    if (!valid()) {
        throw std::exception();
    }
    value_node = map.elements[key_node].second.next[value_node];
    value_count += 1;
    if (value_node == -1 || value_count >= map.elements[key_node].second.size) {
        key_node = map.next[key_node];
        key_count += 1;
        value_node = map.elements[key_node].second.head;
        value_count = 0;
    }
}

bool SMMIterator::valid() const{
    // Complexity: theta(1)
    if (key_node != -1 && key_count < map._size) {
        return true;
    }
    return false;
}

TElem SMMIterator::getCurrent() const{
    // Complexity:
    if (!valid()) {
        throw std::exception();
    }
    int key = map.elements[key_node].first;
    int value = map.elements[key_node].second.elements[value_node];
    return TElem {key, value};
}























