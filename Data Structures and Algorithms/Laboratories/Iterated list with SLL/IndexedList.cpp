#include <exception>

#include "IndexedList.h"
#include "ListIterator.h"


IndexedList::IndexedList() {
    // Complexity: theta(1);
    this->list = new SLL();
}


int IndexedList::size() const {
    // Complexity: O(n)
    int size = 0;
    node* listNode = this->list->head;
    while (listNode != nullptr) {
        size += 1;
        listNode = listNode->next;
    }
    return size;
}


bool IndexedList::isEmpty() const {
    // Complexity: theta(1)
    return this->list->head == nullptr;
}


TElem IndexedList::getElement(int pos) const {
    // Complexity: O(n)
    if (pos < 0 || pos > this->size()) {
        throw std::exception(); // if pos is not valid
    }
    node* listNode = this->list->head;
    int current = 0;
    while (listNode != nullptr) {
        if (current == pos) {
            return listNode->elem;
        }
        current += 1;
        listNode = listNode->next;
    }
    return NULL_TELEM;
}


TElem IndexedList::setElement(int pos, TElem e) {
    // Complexity: O(n)
    if (pos < 0 || pos > this->size()) {
        throw std::exception(); // if pos is not valid
    }
    node* listNode = this->list->head;
    int current = 0;
    while (listNode != nullptr) {
        if (current == pos) {
            TElem previousValue = listNode->elem;
            listNode->elem = e;
            return previousValue;
        }
        current += 1;
        listNode = listNode->next;
    }
    return NULL_TELEM;
}


void IndexedList::addToEnd(TElem e) {
    // Complexity: O(n)
    node* newNode = new node();
    newNode->elem = e;
    newNode->next = nullptr;
    if(this->list->head == nullptr) {
        this->list->head = newNode;
    }
    else {
        node* listNode = this->list->head;
        bool flag = true;
        while (flag) {
            if (listNode->next != nullptr) {
                listNode = listNode->next;
            }
            else {
                flag = false;
            }
        }
        listNode->next = newNode;
        newNode->next = nullptr;
    }
}


void IndexedList::addToPosition(int pos, TElem e) {
    // Complexity: O(n)
    if (pos < 0 || pos > this->size()) {
        throw std::exception(); // if pos is not valid
    }
    node* newNode = new node();
    newNode->elem = e;

    if (pos == 0) {
        node* headNode = this->list->head;
        this->list->head = newNode;
        this->list->head->next = headNode;
    }
    else {
        node* listNode = this->list->head;
        int current = 0;
        while (listNode != nullptr) {
            if (current == pos - 1) {
                node* nextNode = listNode->next;
                listNode->next = newNode;
                newNode->next = nextNode;
                return;
            }
            current += 1;
            listNode = listNode->next;
        }
    }
 }


TElem IndexedList::remove(int pos) {
    // Complexity: O(n)
    if (pos < 0 || pos >= this->size()) {
        throw std::exception(); // if pos is not valid
    }
    if (pos == 0) {
        node* headNode = this->list->head;
        this->list->head = this->list->head->next;
        return headNode->elem;
    }
    if(pos == this->size() - 1) {
        node *listNode = this->list->head;
        int current = 0;
        while (listNode != nullptr) {
            if (current == pos - 1) {
                node *nextNode = listNode->next;
                listNode->next = nullptr;
                return nextNode->elem;
            }
            current += 1;
            listNode = listNode->next;
        }
    }
    node *listNode = this->list->head;
    int current = 0;
    while (listNode != nullptr) {
        if (current == pos - 1) {
            node *nextNode = listNode->next;
            listNode->next = nextNode->next;
            return nextNode->elem;
        }
        current += 1;
        listNode = listNode->next;
    }
    return NULL_TELEM;
}


int IndexedList::search(TElem e) const {
    // Complexity: O(n)
    node* listNode = this->list->head;
    int current = 0;
    while(listNode != nullptr) {
        if (listNode->elem == e) {
            return current;
        }
        current += 1;
        listNode = listNode->next;
    }
    return -1;
}


ListIterator IndexedList::iterator() const {
    // Complexity: theta(1)
    return ListIterator(*this);
}


IndexedList::~IndexedList() {
    // Complexity: theta(1)
    delete this->list;
}