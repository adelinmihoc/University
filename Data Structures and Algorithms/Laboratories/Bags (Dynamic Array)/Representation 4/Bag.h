#pragma once

#define NULL_TELEM -11111;

typedef int TElem;

class BagIterator;

class Bag {

private:
	int bag_lenght;
	int bag_size;
	int bag_capacity;
	TElem* bag_array;
	TElem minimumElement;
	void resize();
	
	friend class BagIterator;
public:
	void ShowElems();

	//constructor
	Bag();

	//adds an element to the bag
	void add(TElem e);

	//removes one occurence of an element from a bag
	//returns true if an eleent was removed, false otherwise (if e was not part of the bag)
	bool remove(TElem e);

	//checks if an element appearch is the bag
	bool search(TElem e) const;

	//returns the number of occurrences for an element in the bag
	int nrOccurrences(TElem e) const;

	//returns the number of elements from the bag
	int size() const;

	//returns an iterator for this bag
	BagIterator iterator() const;

	//checks if the bag is empty
	bool isEmpty() const;

	//destructor
	~Bag();
};