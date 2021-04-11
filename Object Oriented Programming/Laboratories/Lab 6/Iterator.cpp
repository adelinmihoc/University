#include "Iterator.h"


ApprenticeIterator::ApprenticeIterator(/*DynamicVector<GuardianStatue> stats*/) {
	//this->statues = stats;
	this->current = 0;
}


void ApprenticeIterator::add(const GuardianStatue& stat) {
	this->statues.addItem(stat);
}



void ApprenticeIterator::next() {
	this->current += 1;
	if (this->statues.getSize() == this->current) {
		this->current = 0;
	}
}


GuardianStatue ApprenticeIterator::getStatue() {
	return this->statues.getItem(this->current);
}


DynamicVector<GuardianStatue> ApprenticeIterator::getAll() {
	return this->statues;
}



