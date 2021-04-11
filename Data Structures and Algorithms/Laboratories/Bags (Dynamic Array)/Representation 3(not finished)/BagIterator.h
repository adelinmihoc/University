#include "Bag.h"

class BagIterator {
	friend class Bag;
	
private:
	const Bag& bag;

	TElem* items;
	int* positions;
	int positions_length;
	int current;
	int items_length;

	BagIterator(const Bag& c);
public:
	void first();
	void next();
	TElem getCurrent() const;
	bool valid() const;
};
