#pragma once
#include <vector>
#include <utility>


typedef int TElem;
typedef int TPriority;
typedef std::pair<TElem, TPriority> Element;
typedef bool (*Relation)(TPriority p1, TPriority p2);


class PriorityQueue {
private:
    // Representation with binary heap
    int capacity;
    int length;
    Element* elements;
    Relation relation;
    void resize();
    void bubble_up(int position);
    void bubble_down(int position);
public:
	//implicit constructor
	PriorityQueue(Relation r);

	//pushes an element with priority to the queue
	void push(TElem e, TPriority p);

	//returns the element with the highest priority with respect to the order relation
	//throws exception if the queue is empty
	Element top()  const;

	//removes and returns the element with the highest priority
	//throws exception if the queue is empty
	Element pop();

	//checks if the queue is empty
	bool isEmpty() const;

	//destructor
	~PriorityQueue();

};