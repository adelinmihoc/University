#include "Bag.h"

class BagIterator {
	friend class Bag;

private:
	const Bag& bag;

	TElem* items;
	int current;
	int size;

	BagIterator(const Bag& c);
public:
	void first();
	void next();
	TElem getCurrent() const;
	bool valid() const;
};
