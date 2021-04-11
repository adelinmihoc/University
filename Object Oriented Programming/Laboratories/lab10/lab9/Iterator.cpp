#include "Iterator.h"


ApprenticeIterator::ApprenticeIterator(/*DynamicVector<GuardianStatue> stats*/) {
    //this->statues = stats;
    this->current = -1; // -1 means uninitialised
}


void ApprenticeIterator::add(const GuardianStatue& stat) {
    this->statues.push_back(stat);
}


void ApprenticeIterator::next() {
    this->current += 1;
    if (this->statues.size() == this->current) {
        this->current = 0;
    }
}


GuardianStatue ApprenticeIterator::getStatue() {
    return this->statues[this->current];
}


std::vector<GuardianStatue> ApprenticeIterator::getAll() {
    return this->statues;
}



