#pragma once


//DO NOT CHANGE THIS PART
#include <vector>
#include <utility>
#include <iostream>

typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -11111
#define NULL_TELEM pair<TKey, TValue>(-11111, -11111);
using namespace std;
class SMMIterator;
typedef bool(*Relation)(TKey, TKey);


struct SLLA_values {
    TValue* elements;
    int size;
    int* next;
    int capacity;
    int head;
    int first_empty;

    SLLA_values() {
        // Complexity: theta(n)
        this->capacity = 2;
        this->elements = new TValue[this->capacity];
        this->next = new int[this->capacity];
        this->head = -1;
        for (int i = 0; i < this->capacity; i++) {
            this->next[i] = i + 1;
        }
        this->next[this->capacity - 1] = -1;
        this->first_empty = 0;
        this->size = 0;
    }
    ~SLLA_values() = default;

    void free_memory() const {
        delete [] this->elements;
        delete [] this->next;
    }

    int length() const {
        // Complexity: theta(1)
        return this->size;
    }

    void resize() {
        // Complexity: theta(n)
        int new_capacity = 2 * this->capacity;
        auto* new_elements = new TValue[new_capacity];
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

    void add(TValue v) {
        // Complexity: O(1)
        if (this->first_empty == -1) {
            this->resize();
        }
        auto next_position = this->first_empty; // position where the element will be
        this->elements[next_position] = v; // put it
        this->first_empty = this->next[next_position]; // get next empty position
        this->next[next_position] = -1; // mark the end of active positions
        if (this->head == -1) { // first element in the SLLA
            this->head = next_position;
        } else {
            this->next[next_position] = this->head;
            this->head = next_position;
        }
        this->size += 1;
    }

    bool remove(TValue v) {
        // Complexity: O(n)
        int previous_node = -1;
        int current_node = this->head;
        int current_position = 0;
        while (current_node != -1 && this->elements[current_node] != v && current_position < this->size - 1) {
            previous_node = current_node;
            current_node = this->next[current_node];
        }
        if (current_node != -1) {
            if (current_node == head) {
                this->head = this->next[this->head];
                this->next[current_node] = this->next[this->first_empty];
                this->first_empty = current_node;
            } else {
                this->next[previous_node] = this->next[current_node];
                this->next[current_node] = this->first_empty;
                this->first_empty = current_node;
            }
            this->size -= 1;
            return true;
        }
        return false;
    }

    std::vector<TValue> get_all() const {
        // Complexity: O(n)
        std::vector<TValue> result;
        int current_node = this->head;
        int count = 0;
        while (current_node != -1 && count < this->size) {
            result.push_back(this->elements[current_node]);
            current_node = this->next[current_node];
            count++;
        }
        return result;
    }

    TValue get_element(int pos) const {
        int current_node = this->head;
        int count = 0;
        while (current_node != -1 && count < pos - 1) {
            current_node = this->next[current_node];
            count++;
        }
        if (current_node != -1) {
            return this->elements[current_node];
        }
        return NULL_TVALUE;
    }
    bool search(TValue v) {
        // Complexity: O(n)
        int current = this->head;
        while (current != -1 && this->elements[current] != v) {
            current = this->next[current];
        }
        if (current != -1) {
            return true;
        } else {
            return false;
        }
    }
};


class SortedMultiMap {
	friend class SMMIterator;
    private:
        Relation relation;
        int capacity;
        std::pair<TKey, SLLA_values> *elements;
        int* next;
        int head;
        int first_empty;
        int _size; // number of keys
        int number_of_elements;
        void resize();
    public:
    std::vector<TKey> key_set() const;

    void insert_at_position(const pair<int, SLLA_values>& element, int pos);

    std::vector<std::pair<TKey, SLLA_values> > get_all();
    // constructor
    explicit SortedMultiMap(Relation r);

	//adds a new key value pair to the sorted multi map
    void add(TKey c, TValue v);

	//returns the values belonging to a given key
    vector<TValue> search(TKey c) const;

	//removes a key value pair from the sorted multimap
	//returns true if the pair was removed (it was part of the multimap), false if nothing is removed
    bool remove(TKey c, TValue v);

    //returns the number of key-value pairs from the sorted multimap
    int size() const;

    //verifies if the sorted multi map is empty
    bool isEmpty() const;

    // returns an iterator for the sorted multimap. The iterator will returns the pairs as required by the relation (given to the constructor)	
    SMMIterator iterator() const;

    // destructor
    ~SortedMultiMap();
};
