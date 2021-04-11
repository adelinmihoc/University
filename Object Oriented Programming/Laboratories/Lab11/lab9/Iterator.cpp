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
    if (int(this->statues.size()) == this->current) {
        this->current = 0;
    }
}


GuardianStatue ApprenticeIterator::getStatue() {
    if (this->current >= int(this->statues.size())) {
        throw std::exception();
    }
    if (this->current != -1) {
        return this->statues[this->current];
    }
    throw std::exception();
}


std::vector<GuardianStatue> ApprenticeIterator::getAll() {
    return this->statues;
}



