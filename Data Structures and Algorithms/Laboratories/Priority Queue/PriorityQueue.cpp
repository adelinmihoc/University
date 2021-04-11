#include "PriorityQueue.h"
#include <exception>


PriorityQueue::PriorityQueue(Relation r) {
    // Complexity: Theta(1)
	this->capacity = 10000; // resize not implemented
	this->length = 0;
	this->elements = new Element[capacity];
	this->relation = r;
}


void PriorityQueue::push(TElem e, TPriority p) {
    // Complexity: O(log2n)
	if (this->length == this->capacity) {
        resize();
	}
	Element elem = std::make_pair(e, p);
	this->elements[length + 1] = elem;
	this->length += 1;
	bubble_up(this->length);
}

//throws exception if the queue is empty
Element PriorityQueue::top() const {
    // Complexity: Theta(1)
	if (this->length == 0) {
        throw std::exception();
    } else {
	    return this->elements[1];
	}
}

Element PriorityQueue::pop() {
    // Complexity: O(log2n)
	if (this->length == 0) {
        throw std::exception();
	} else {
        Element element = this->top();
        this->elements[1] = this->elements[this->length];
        this->length -= 1;
        bubble_down(1);
        return element;
    }
}

bool PriorityQueue::isEmpty() const {
    // Complexity: Theta(1)
	return this->length == 0;
}

PriorityQueue::~PriorityQueue() {
    // Complexity: Theta(1)
	delete[] this->elements;
}

void PriorityQueue::resize() {
    // Complexity: Theta(n)

}

void PriorityQueue::bubble_up(int position) {
    // Complexity: O(log2n)
    Element elem = this->elements[position];
    int parent = position / 2;
    while (position > 1 and this->relation(elem.second, this->elements[parent].second)) {
        this->elements[position] = this->elements[parent];
        position = parent;
        parent = position / 2;
    }
    this->elements[position] = elem;
}

void PriorityQueue::bubble_down(int position) {
    // Complexity: O(log2n)
    Element elem = this->elements[position];
    while (position < this->length) {
        int maxChild = -1;
        if (position * 2 <= this->length) {
            maxChild = position * 2;
        }
        if (position * 2 + 1 <= this->length and this->relation(this->elements[2 * position + 1].second, this->elements[2 * position].second)) {
            maxChild = position * 2 + 1;
        }
        if (maxChild != -1 and this->relation(this->elements[maxChild].second, elem.second)) {
            std::swap(this->elements[position], this->elements[maxChild]);
            position = maxChild;
        } else {
            position = this->length + 1;
        }
    }
}

