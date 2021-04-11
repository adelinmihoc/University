#include "Bag.h"

class BagIterator {
	friend class Bag;
private:
	const Bag& bag;

	TElem* iterator_elems;
	int iterator_current;
	int iterator_size;

	BagIterator(const Bag& c);
public:
	void first();
	void next();
	TElem getCurrent() const;
	bool valid() const;
};
