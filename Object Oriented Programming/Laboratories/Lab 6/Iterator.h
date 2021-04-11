#pragma once
#include "DynamicArray.h"
#include "Domain.h"
#include "Repository.h"


class ApprenticeIterator {
private:
	DynamicVector<GuardianStatue> statues;
	int current;
public:
	//Constructor function
	ApprenticeIterator(/*DynamicVector<GuardianStatue> statues*/);


	//Initialise the 'statues' field
	void add(const GuardianStatue& stat);


	//Moves to the next statue
	void next();


	//Getter function for the current statue
	GuardianStatue getStatue();


	//Getter function for all statues
	DynamicVector<GuardianStatue> getAll();
};