#pragma once

#include "SortedMultiMap.h"


class SMMIterator{
	friend class SortedMultiMap;
private:
	//DO NOT CHANGE THIS PART
	const SortedMultiMap& map;
	explicit SMMIterator(const SortedMultiMap& map);

    int key_node;
    int value_node;
    int key_count;
    int value_count;
public:
	void first();
	void next();
	bool valid() const;
   	TElem getCurrent() const;
};

