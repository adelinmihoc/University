#include "ListIterator.h"
#include "IndexedList.h"
#include <exception>


ListIterator::ListIterator(const IndexedList& list) : list(list) {
    // Complexity: theta(1)
    this->current = this->list.list->head;
    this->position = 0;
}

void ListIterator::first(){
    // Complexity: theta(1)
    this->current = this->list.list->head;
    this->position = 0;
}

void ListIterator::next(){
    // Complexity: theta(1)
    if (!this->valid()) {
        throw std::exception();
    }
    this->current = this->current->next;
    this->position += 1;
}

bool ListIterator::valid() const {
    // Complexity: theta(1)
    return this->current != nullptr;
}

TElem ListIterator::getCurrent() const{
    // Complexity: theta(1)
    if (this->valid()) {
        return this->current->elem;
    }
    throw std::exception();
}

void ListIterator::jumpBackward(int k) {
    // Complexity: O(n)
    if (this->position - k < 0 || k <= 0) {
        throw std::exception();
    }
    int toPosition = this->position - k;
    this->first();
    while (this->valid()) {
        this->next();
        if (this->position == toPosition) {
            return;
        }
    }
}
