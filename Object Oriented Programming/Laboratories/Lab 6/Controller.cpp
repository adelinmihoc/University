#include "Controller.h"


void Enchantment::addGuardianStatue(const std::string& powerWordName, const std::string& material, const int& age, const std::string corporealForm) {
	GuardianStatue guardStat = { powerWordName, material, age, corporealForm };
	try {
		encyclopedia.addStatue(guardStat);
	}
	catch (std::exception&) {
		throw std::exception();
	}
}


void Enchantment::deleteGuardianStatue(const std::string& powerWordName) {
	try {
		encyclopedia.deleteStatue(powerWordName);
	}
	catch (std::exception&) {
		throw std::exception();
	}
}


void Enchantment::updateGuardianStatue(const std::string& powerWordName, const std::string& newMaterial, const int& newAge, const std::string newCorporealForm) {
	GuardianStatue guardStat = { powerWordName, newMaterial, newAge, newCorporealForm };
	try {
		encyclopedia.updateStatue(guardStat);
	}
	catch (std::exception&) {
		throw std::exception();
	}
}


int Enchantment::getSize() const {
	return encyclopedia.getSize();
}


DynamicVector<GuardianStatue> Enchantment::getAllGuardianStatues() {
	return encyclopedia.getAllStatues();
}


////////////////////////////////////////////////////////////////////////////


DynamicVector<GuardianStatue> Enchantment::getAllApprenticeGuardianStatues()
{
	return apprenticeEncyclopedia.getAllStatues();
}


void Enchantment::initialiseIterator() {
	DynamicVector<GuardianStatue> stats = this->encyclopedia.getAllStatues();
	for (int i = 0; i < stats.getSize(); i++) {
		this->encyclopediaIterator.add(stats.getItem(i));
	}
}


GuardianStatue Enchantment::nextGuardianStatues() {
	GuardianStatue nextStatue = this->encyclopediaIterator.getStatue();
	this->encyclopediaIterator.next();
	return nextStatue;
}


void Enchantment::saveGuardianStatue(std::string powerWordName) {
	int positionOfStat = this->searchGuardianStatue(powerWordName);
	if (positionOfStat == -1) {
		throw std::exception();
	}
	this->apprenticeEncyclopedia.addStatue(this->encyclopedia.getAllStatues().getItem(positionOfStat));
}


int Enchantment::searchGuardianStatue(std::string powerWordName) {
	for (int i = 0; i < this->encyclopedia.getSize(); i++) {
		if (this->encyclopedia.getAllStatues().getItem(i).getPowerWordName() == powerWordName) {
			return i;
		}
	}
	return -1;
}


DynamicVector<GuardianStatue> Enchantment::getAllApprenticesStatuesByMaterial(std::string material) {
	DynamicVector<GuardianStatue> result;
	DynamicVector<GuardianStatue> allStatues = this->getAllApprenticeGuardianStatues();
	for (int i = 0; i < allStatues.getSize(); i++) {
		if (allStatues.getItem(i).getMaterial() == material) {
			result.addItem(allStatues.getItem(i));
		}
	}
	if (result.getSize() == 0) {
		return this->getAllGuardianStatues();
	}
	return result;
}



DynamicVector<GuardianStatue> Enchantment::getAllApprenticeStatuesByMaterialAndAge(std::string material, int age) {
	DynamicVector<GuardianStatue> result;
	DynamicVector<GuardianStatue> allStatues = this->getAllApprenticesStatuesByMaterial(material);
	for (int i = 0; i < allStatues.getSize(); i++) {
		if (allStatues.getItem(i).getAge() < age) {
			result.addItem(allStatues.getItem(i));
		}
	}
	return result;
}
